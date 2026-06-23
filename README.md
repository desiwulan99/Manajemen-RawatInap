# Hospital Inpatient Queue Management System

## Overview
Hospital Inpatient Queue Management System is a desktop-based application developed using **C++**, **Raylib**, and **RayGUI**. This project was created as a final assignment for the Data Structures course and demonstrates the integration of multiple data structures into a single hospital management application.

The system manages patient admissions, room allocation, waiting lists, patient archives, hospital route navigation, and activity logging through an interactive graphical user interface (GUI).

---

## Features

### Authentication System
* User login validation
* Username and password storage using Hash Table

### Room Management
* Real-time inpatient room monitoring
* Automatic room allocation based on room class
* Round-robin room assignment mechanism

### Patient Admission Queue
* FIFO admission processing
* Circular Linked List Queue implementation

### Waiting List Management
* Priority-based waiting list
* Emergency Department (ER) patients receive higher priority
* Patient cancellation and removal support

### Patient Checkout Archive
* Store discharged patient records
* Fast patient search using AVL Tree

### Hospital Route Map
* Hospital navigation visualization
* Shortest path search using BFS algorithm

### Activity Log
* Records all system activities
* Stack-based implementation (LIFO)

### Information Ticker
* Displays hospital announcements
* Bubble Sort used for priority-based message ordering

---

## Data Structures Used

| Data Structure                    | Purpose                           |
| --------------------------------- | --------------------------------- |
| Hash Table                        | User Authentication               |
| Array + Bubble Sort               | Running Text / Information Ticker |
| Graph + BFS                       | Hospital Route Navigation         |
| Stack (LIFO)                      | Activity Logs                     |
| Circular Linked List Queue (FIFO) | Patient Admission Queue           |
| Priority Queue                    | Waiting List Management           |
| AVL Tree                          | Patient Archive Search            |

---

## System Workflow
1. User logs into the system.
2. New patient registration.
3. Patient enters admission queue.
4. Admission process allocates available rooms.
5. If no room is available, patient enters waiting list.
6. Checkout process stores patient data in AVL Tree archive.
7. Archived patients can be searched by ID.
8. All activities are recorded in the activity log.

---

## Technologies
* C++
* Raylib
* RayGUI
* Object-Oriented Programming (OOP)

---

## Project Structure
```text
├── main.cpp
├── AuthHashTable.h/.cpp
├── SimpleTicker.h/.cpp
├── RSGraph.h/.cpp
├── ActivityStack.h/.cpp
├── AdmisiQueue.h/.cpp
├── WaitingListPQ.h/.cpp
├── AVLTree.h/.cpp
├── Kamar.h/.cpp
├── Pasien.h
├── AppFont.h
└── assets/
```

---

## Learning Outcomes
This project demonstrates practical implementation of:

* Linear Data Structures
* Non-Linear Data Structures
* Searching Algorithms
* Sorting Algorithms
* Queue Management Systems
* Memory Management with Dynamic Allocation
* GUI-based Desktop Application Development

---

## Authors
Group 3 – Data Structures Final Project
- Khayla Adelia Hermawan
- Desi Wulan Sari
-Feby Valentine Samsoir

Developed as part of the Data Structures course assignment.