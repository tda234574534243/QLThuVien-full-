Library Management System
Project for Data Structures & Algorithms Course (CTDL & GT)
Project Overview
This project involves building a Library Management System to handle daily operations of a library, including borrowing and returning books, and searching for book information. The system allows librarians to manage books, readers, and borrowing records efficiently while storing all data in files.

Key Information
Project Code: PRO_CTDL_3
Submission Format: Submit via Google Classroom.
Deadline: ... / ... / ......
Scope: Covers Chapters 2, 3, 4, and 5 of the course.
Learning Outcomes
Develop an understanding of file-based data management.
Practice data structure techniques such as arrays, lists, and queues.
Implement core algorithms for searching, updating, and managing datasets.
Apply user access controls and error-handling mechanisms.
System Features
1. User Authentication
Login Screen:

Users must provide a valid username and password stored in Admin.txt.
Users are locked out after three incorrect attempts.
Allows exiting the system by pressing the ESC key.
Security:

Passwords are masked as * during input.
2. Main Menu
After successful login, the main menu offers two primary modules:

Book Management
Borrowing Management
3. Book Management
Manage the library’s book inventory with the following functionalities:

3.1 Display Books
Show detailed information for all books, including:
Book ID, Title, Author, Publisher, Price, Year Published, Page Count, Storage Date, and Status.
3.2 Add a Book
Add new books to the system.
Validation:
Prevent duplicate entries by checking unique Book IDs.
Data is appended to the Sach.txt file.
3.3 Delete a Book
Delete a book by entering its Book ID.
Conditions for deletion:
Book status must be 0 (not borrowed).
The book must exist in the library.
Updates are saved to the Sach.txt file.
4. Borrowing Management
Handle borrowing and returning books effectively:

4.1 Display Borrowing Records
Show details of all borrowing records stored in the PhieuMuon.txt file.
4.2 Borrow a Book
Enter Book ID and Reader ID to create a new borrowing record.
Conditions for borrowing:
The book must not be currently borrowed (status 0).
Reader ID must exist in the reader list.
Updates:
Book status is set to the borrowing record number.
Files Sach.txt and PhieuMuon.txt are updated.
4.3 Return a Book
Enter the borrowing record number to return a book.
Conditions for return:
The borrowing record must exist and have a status of 1 (borrowed).
Updates:
Book status is reset to 0.
Files Sach.txt and PhieuMuon.txt are updated.
Additional Requirements
Error Handling:

Notify users of errors and allow them to retry or choose another function.
Ensure all invalid inputs or operations are handled gracefully.
User Interface:

Use colors for better readability.
Simplify navigation with clear prompts.
File Structure
1. Sach.txt
Stores book information:

Fields: Book ID, Title, Author, Publisher, Price, Year Published, Page Count, Storage Date, Status.
2. BanDoc.txt
Stores reader information:

Fields: Reader ID, Name, Registration Date.
3. PhieuMuon.txt
Stores borrowing records:

Fields: Record Number, Reader ID, Book ID, Borrow Date, Return Date, Status.
4. Admin.txt
Stores admin credentials for authentication:

Fields: Username, Password (hashed).
How to Run
Compile and execute the program using a C++ compiler or IDE.
Follow the prompts to login and navigate the system.
Ensure required data files (Sach.txt, BanDoc.txt, PhieuMuon.txt, and Admin.txt) are available in the program directory.
Future Enhancements
Add a graphical user interface (GUI) for better user experience.
Implement overdue notifications for unreturned books.
Add a search feature for books and readers.
Contact
For any queries or assistance, contact your instructor via Google Classroom.
