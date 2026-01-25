import os
from datetime import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Create tables if they don't exist
db.execute("""
    CREATE TABLE IF NOT EXISTS users (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        username TEXT NOT NULL UNIQUE,
        display_name TEXT NOT NULL,
        hash TEXT NOT NULL
    )
""")

# Add new columns if they don't exist (for existing databases)
try:
    db.execute("ALTER TABLE users ADD COLUMN display_name TEXT DEFAULT 'User'")
except:
    pass

db.execute("""
    CREATE TABLE IF NOT EXISTS transactions (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        user_id INTEGER NOT NULL,
        title TEXT NOT NULL,
        type TEXT NOT NULL,
        category TEXT NOT NULL,
        amount REAL NOT NULL,
        description TEXT,
        date TEXT NOT NULL,
        FOREIGN KEY(user_id) REFERENCES users(id)
    )
""")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
def index():
    """Show app introduction page"""
    return render_template("intro.html")


@app.route("/dashboard")
@login_required
def dashboard():
    """Show portfolio of transactions"""
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY date DESC LIMIT 10",
        session["user_id"]
    )
    
    # Calculate totals
    income = db.execute(
        "SELECT COALESCE(SUM(amount), 0) as total FROM transactions WHERE user_id = ? AND type = 'income'",
        session["user_id"]
    )[0]["total"]
    
    expenses = db.execute(
        "SELECT COALESCE(SUM(amount), 0) as total FROM transactions WHERE user_id = ? AND type = 'expense'",
        session["user_id"]
    )[0]["total"]
    
    balance = income - expenses
    
    return render_template("dashboard.html", transactions=transactions, balance=balance, income=income, expenses=expenses)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = ? ORDER BY date DESC",
        session["user_id"]
    )
    return render_template("history.html", transactions=transactions)


@app.route("/manage")
@login_required
def manage():
    """Show manage page for editing transactions"""
    transaction_id = request.args.get("id")
    if transaction_id:
        transaction = db.execute(
            "SELECT * FROM transactions WHERE id = ? AND user_id = ?",
            transaction_id, session["user_id"]
        )
        if transaction:
            return render_template("manage.html", transaction=transaction[0])
    return render_template("manage.html")


@app.route("/manage", methods=["POST"])
@login_required
def manage_post():
    """Handle manage operations"""
    action = request.form.get("action")
    transaction_id = request.form.get("id")
    
    if action == "delete" and transaction_id:
        db.execute(
            "DELETE FROM transactions WHERE id = ? AND user_id = ?",
            transaction_id, session["user_id"]
        )
        flash("Transaction deleted successfully!")
        return redirect("/history")
    
    elif action == "edit" and transaction_id:
        title = request.form.get("title")
        transaction_type = request.form.get("type")
        category = request.form.get("category")
        amount = request.form.get("amount")
        description = request.form.get("description")
        
        if not title or not transaction_type or not category or not amount:
            return apology("All fields required")
        
        try:
            amount = float(amount)
            if amount <= 0:
                return apology("Amount must be positive")
        except ValueError:
            return apology("Invalid amount")
        
        db.execute(
            "UPDATE transactions SET title = ?, type = ?, category = ?, amount = ?, description = ? WHERE id = ? AND user_id = ?",
            title, transaction_type, category, amount, description, transaction_id, session["user_id"]
        )
        flash("Transaction updated successfully!")
        return redirect("/history")
    
    return apology("Invalid action")


@app.route("/add")
@login_required
def add():
    """Show add transaction form"""
    return render_template("add.html")


@app.route("/add", methods=["POST"])
@login_required
def add_post():
    """Add new transaction"""
    title = request.form.get("title")
    transaction_type = request.form.get("type")
    category = request.form.get("category")
    amount = request.form.get("amount")
    description = request.form.get("description")
    
    if not title or not transaction_type or not category or not amount:
        return apology("All fields required")
    
    try:
        amount = float(amount)
        if amount <= 0:
            return apology("Amount must be positive")
    except ValueError:
        return apology("Invalid amount")
    
    db.execute(
        "INSERT INTO transactions (user_id, title, type, category, amount, description, date) VALUES (?, ?, ?, ?, ?, ?, ?)",
        session["user_id"], title, transaction_type, category, amount, description, datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    )
    
    flash("Transaction added successfully!")
    return redirect("/dashboard")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    session.clear()
    
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        
        if not username:
            return apology("Must provide username")
        elif not password:
            return apology("Must provide password")
        
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return apology("Invalid username and/or password")
        
        session["user_id"] = rows[0]["id"]
        return redirect("/dashboard")
    
    return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")


@app.route("/profile")
@login_required
def profile():
    """Show user profile"""
    user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    if not user:
        return redirect("/logout")
    return render_template("profile.html", user=user[0])


@app.route("/profile", methods=["POST"])
@login_required
def profile_post():
    """Update user profile"""
    action = request.form.get("action")
    
    if action == "update_profile":
        display_name = request.form.get("display_name")
        
        if not display_name:
            return apology("Display name required")
        
        db.execute(
            "UPDATE users SET display_name = ? WHERE id = ?",
            display_name, session["user_id"]
        )
        flash("Profile updated successfully!")
        
    elif action == "change_password":
        current_password = request.form.get("current_password")
        new_password = request.form.get("new_password")
        confirm_password = request.form.get("confirm_password")
        
        if not current_password or not new_password or not confirm_password:
            return apology("All password fields required")
        
        user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]
        if not check_password_hash(user["hash"], current_password):
            return apology("Current password incorrect")
        
        if new_password != confirm_password:
            return apology("New passwords don't match")
        
        new_hash = generate_password_hash(new_password)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", new_hash, session["user_id"])
        flash("Password changed successfully!")
        
    elif action == "delete_account":
        confirm = request.form.get("confirm_delete")
        if confirm != "DELETE":
            return apology("Type DELETE to confirm")
        
        db.execute("DELETE FROM transactions WHERE user_id = ?", session["user_id"])
        db.execute("DELETE FROM users WHERE id = ?", session["user_id"])
        session.clear()
        flash("Account deleted successfully")
        return redirect("/")
    
    return redirect("/profile")

# AI generated route
@app.route("/api/user-info")
@login_required
def user_info():
    """Get user info for navbar"""
    user = db.execute("SELECT display_name FROM users WHERE id = ?", session["user_id"])
    if user:
        return jsonify(user[0])
    return jsonify({'display_name': 'User'})


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        display_name = request.form.get("display_name")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        
        if not username:
            return apology("Must provide username")
        elif not display_name:
            return apology("Must provide display name")
        elif not password:
            return apology("Must provide password")
        elif not confirmation:
            return apology("Must confirm password")
        elif password != confirmation:
            return apology("Passwords don't match")
        
        # Check if username already exists
        existing_user = db.execute("SELECT * FROM users WHERE username = ?", username)
        if existing_user:
            return apology("Username already exists")
        
        # Hash password and insert user
        hash_password = generate_password_hash(password)
        try:
            user_id = db.execute(
                "INSERT INTO users (username, display_name, hash) VALUES (?, ?, ?)",
                username, display_name, hash_password
            )
            session["user_id"] = user_id
            flash("Registered successfully!")
            return redirect("/dashboard")
        except:
            return apology("Registration failed")
    
    return render_template("register.html")

