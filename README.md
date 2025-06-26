# Personal Finance Manager

## Overview
Personal Finance Manager is a C++ console-based application designed to help users manage their personal finances. It allows users to track income and expense transactions, calculate taxes, set budgets, generate reports, and save/load data to/from a file. The application supports features like transaction management, budget tracking for categories (Food, Travel, Education), and customizable financial reports.

## Features
- **User Management**: Store and update user information (name, address, mobile number, age).
- **Transaction Management**:
  - Record income and expense transactions with details like source, amount, date, month, and year.
  - Search transactions by date or type (income/expense).
  - Delete transactions based on source.
  - View the 5 most recent transactions.
- **Tax Calculation**:
  - Calculates income tax based on predefined slabs (per FBR rules).
  - Calculates sales tax at a fixed 17% GST rate.
  - Tracks total income and sales tax.
- **Budget Management**:
  - Set budgets for Food, Travel, and Education with weekly, monthly, or yearly durations.
  - Track spending and receive warnings when exceeding budget limits.
  - Reset budgets as needed.
- **Reporting**:
  - Generate customizable reports with filters for transaction type, amount range, date, and tax information.
  - Save reports to text files.
- **Data Persistence**:
  - Save user, account, transaction, and budget data to a file (`data.txt`).
  - Load data from the file on program startup.

## Project Structure
- **Source File**: `Personal_Finance_Manager.cpp`
- **Data File**: `data.txt` (used for saving/loading user data)
- **Classes**:
  - `User`: Manages user information and provides an interface for financial operations.
  - `Account`: Handles transactions, balances, and report generation.
  - `Transaction`: Base class for `Income` and `Expense` transactions.
  - `Taxes`: Base class for `IncomeTax` and `SalesTax` to calculate taxes.
  - `Budget`: Manages budgets for specific categories (Food, Travel, Education).
  - `Report`: Generates and saves customizable financial reports.

## Prerequisites
- C++ compiler (e.g., g++ with C++11 or later)
- Standard C++ libraries (`iostream`, `bits/stdc++.h`, etc.)
- Operating system with console support (Windows/Linux/MacOS)

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/personal-finance-manager.git
