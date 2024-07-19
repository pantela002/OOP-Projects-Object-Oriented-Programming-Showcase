# **OOP Projects: Object-Oriented Programming Showcase**

## Overview

This repository showcases various object-oriented programming (OOP) projects. Each project highlights different aspects of OOP principles and design in C++. 

## Projects

### Problem 1: Phonebook Implementation

**Objective**: Implement a telephone book in C++ that supports various operations, including loading from a CSV file, searching, selecting, deleting, editing, and calling contacts. The phonebook should handle errors using exceptions.

#### Functional Specifications

- **Loading Contacts**:
  - Implement `void Phonebook::loadPhonebook(const string& filepath);` to load contacts from a CSV file.
  - Format: Each line in the CSV file contains a contact with a name and phone number separated by a comma. Phone numbers should be in formats like `+381 xx` or `0xx`.

- **Commands**:
  - `NEW`: Add a new contact.
  - `SEARCH`: Display contacts with names starting with the entered prefix.
  - `SELECT`: Select a contact by name.
  - `DELETE`: Delete the selected contact.
  - `EDIT`: Edit the selected contact’s details.
  - `CALL`: Call the selected contact and store it in call history.
  - `CALL_HISTORY`: Show the last ten called contacts.
  
- **Terminal Interaction**:
  - Implement `void Phonebook::openTerminal();` to interact with the user via the terminal.
  - The terminal should process commands in a loop and exit on the `EXIT` command.

- **Error Handling**:
  - Use a common exception class `PhonebookException` for error handling.
  - Print meaningful error messages to standard output.

- **Technical Requirements**:
  - The system should be efficient, well-commented, modular, and extensible.
  - Use standard library types like `<string>`, `<vector>`, etc.
  - Follow naming conventions for class operations as specified in the task.

#### Example Usage

```plaintext
--------------------------
Welcome to your phonebook!
--------------------------
Enter the command: SEARCH
- Enter the contact name or first few letters: Mil
- 3 contacts have been found:
--- Milan +381 63 1582356
--- Mileva 011 5486236
--- Milos Fakultet 011 145663
Enter the command: SELECT
- Enter the contact name: Milan
- Contact Milan +381 63 1582356 is now selected.
Enter the command: DELETE
- Contact Milan +381 63 1582356 has been deleted.
Enter the command: SELECT
- Enter the contact name: Milan
- No contact has been found.
Enter the command: EXIT
