# Personal Finance Tracker

Video Link: [Personal Finance Tracker](https://youtu.be/-PupXPhkV18)

A comprehensive web-based personal finance management application built with Flask that empowers users to take complete control of their financial health. This modern finance tracker combines intuitive design with powerful features to provide a clean and efficient financial management experience.

## 🌟 Key Features

### 💰 Complete Financial Management
- **Income & Expense Tracking**: Record and categorize all your financial transactions with detailed descriptions
- **Real-time Balance Calculation**: Instantly see your financial status with automatic income vs expense calculations
- **Transaction History**: Comprehensive view of all your financial activities with easy filtering and search
- **Category Organization**: Organize transactions into meaningful categories for better financial insights

### 🔐 Security & Privacy
- **Secure Authentication**: Industry-standard password hashing using Werkzeug security
- **Session Management**: Secure user sessions with automatic timeout protection
- **Data Privacy**: All your financial data remains private and secure on your local system
- **Input Validation**: Comprehensive validation to prevent security vulnerabilities

### 📱 User Experience
- **Responsive Design**: Works seamlessly on desktop, tablet, and mobile devices
- **Intuitive Interface**: Clean, modern design built with Bootstrap for optimal usability
- **Quick Actions**: Easy-to-use forms for adding, editing, and managing transactions
- **Visual Feedback**: Color-coded transaction types and real-time balance updates

## 🚀 Getting Started

### Prerequisites
- Python 3.7 or higher
- pip (Python package installer)

### Installation

1. **Clone or download the project**
   ```bash
   git clone <repository-url>
   cd personal-finance-tracker
   ```

2. **Install dependencies**
   ```bash
   pip install -r requirements.txt
   ```

3. **Initialize the database**
   The application will automatically create the SQLite database and tables on first run.

4. **Run the application**
   ```bash
   flask run
   ```

5. **Access the application**
   Open your web browser and navigate to `http://localhost:5000`

## 📖 How to Use

### Getting Started
1. **Welcome Page**: Visit the homepage to learn about the application features
2. **Register**: Create your account with a unique username and secure password
3. **Login**: Access your personal finance dashboard

### Managing Transactions
1. **Add Transactions**: Use the "Add Transaction" page to record income or expenses
2. **Categorize**: Choose from predefined categories or add custom descriptions
3. **View Dashboard**: Monitor your financial overview with recent transactions and balance summary
4. **Transaction History**: Access complete transaction history with edit capabilities
5. **Manage Entries**: Edit or delete any transaction using the manage functionality

## 🏗️ Technical Architecture

### Backend Technologies
- **Flask**: Lightweight and powerful Python web framework
- **SQLite**: Reliable embedded database for data storage
- **CS50 Library**: Simplified database operations and utilities
- **Werkzeug**: Security utilities for password hashing

### Frontend Technologies
- **Bootstrap 5**: Modern CSS framework for responsive design
- **JavaScript**: Interactive features and form validation
- **HTML5/CSS3**: Semantic markup and custom styling

### Database Schema
- **Users Table**: Secure user account management with hashed passwords and display names
- **Transactions Table**: Comprehensive transaction storage with foreign key relationships

## 💡 Unique Selling Points

### 1. **Simplicity First**
Focused on core finance tracking without unnecessary complexity, making it perfect for users who want straightforward expense management.

### 2. **Global Accessibility**
Designed to work worldwide with support for multiple currencies and regions, making it accessible to users from any country.

### 3. **Complete Privacy**
Your financial data never leaves your system. No cloud storage, no data sharing, complete privacy and control over your sensitive financial information.

### 4. **Educational Value**
Built as a learning project, the codebase is clean, well-documented, and perfect for understanding modern web development practices.

## 🔧 Customization

The application is highly customizable:
- **Categories**: Easily modify income and expense categories
- **Currency**: Adapt for different currencies and regions worldwide
- **Styling**: Customize the appearance with CSS modifications
- **Features**: Add new functionality as needed

## 🤝 Contributing

This project welcomes contributions! Whether you want to:
- Add new features
- Enhance the user interface
- Fix bugs or optimize performance
- Improve documentation

Feel free to fork the project and submit pull requests.

## 📄 License

This project is open source and available under the MIT License.

## 🎯 Future Enhancements

- **Data Visualization**: Charts and graphs for spending analysis
- **Budget Planning**: Advanced budgeting tools and goal setting
- **Export Features**: PDF reports and CSV data export
- **Multi-currency Support**: Enhanced international currency handling
- **Mobile App**: Native mobile application development

---

**Start your journey to better financial health today with Personal Finance Tracker!**
