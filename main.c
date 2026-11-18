#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define MAX_ROOMS 10
#define MONTHLY_RENT 5000

struct Student {
    int id;
    char name[50];
    int roomNumber;
    int rentPaid;
};

struct Room {
    int roomNumber;
    int occupied;
    int studentId;
};

int readInteger(void) {
    int number;
    int ch;

    while (scanf("%d", &number) != 1) {
        printf("Invalid input. Please enter a number: ");
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return number;
}

int findStudent(struct Student students[], int studentCount, int id) {
    int i;

    for (i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            return i;
        }
    }

    return -1;
}

void addStudent(struct Student students[], int *studentCount) {
    int id;

    if (*studentCount >= MAX_STUDENTS) {
        printf("Student list is full.\n");
        return;
    }

    printf("Enter student ID: ");
    id = readInteger();

    if (findStudent(students, *studentCount, id) != -1) {
        printf("This student ID already exists.\n");
        return;
    }

    students[*studentCount].id = id;
    printf("Enter student name: ");

    if (fgets(students[*studentCount].name, sizeof(students[*studentCount].name), stdin) == NULL) {
        printf("Could not read student name.\n");
        return;
    }

    students[*studentCount].name[strcspn(students[*studentCount].name, "\n")] = '\0';

    if (students[*studentCount].name[0] == '\0') {
        printf("Name cannot be empty. Student was not added.\n");
        return;
    }

    students[*studentCount].roomNumber = 0;
    students[*studentCount].rentPaid = 0;
    (*studentCount)++;

    printf("Student added successfully.\n");
}

void allocateRoom(struct Student students[], int studentCount, struct Room rooms[], int roomCount) {
    int id;
    int studentIndex;
    int i;

    printf("Enter student ID: ");
    id = readInteger();

    studentIndex = findStudent(students, studentCount, id);

    if (studentIndex == -1) {
        printf("Student not found. Add the student first.\n");
        return;
    }

    if (students[studentIndex].roomNumber != 0) {
        printf("This student already has room %d.\n", students[studentIndex].roomNumber);
        return;
    }

    for (i = 0; i < roomCount; i++) {
        if (rooms[i].occupied == 0) {
            rooms[i].occupied = 1;
            rooms[i].studentId = id;
            students[studentIndex].roomNumber = rooms[i].roomNumber;
            printf("Room %d allocated successfully.\n", rooms[i].roomNumber);
            return;
        }
    }

    printf("No rooms are available right now.\n");
}

void displayRecords(struct Student students[], int studentCount, struct Room rooms[], int roomCount) {
    int i;

    if (studentCount == 0) {
        printf("No student records found.\n");
    } else {
        printf("\nStudent Records\n");
        printf("-----------------------------------------------\n");
        printf("ID\tName\t\tRoom\tRent Status\n");
        printf("-----------------------------------------------\n");

        for (i = 0; i < studentCount; i++) {
            printf("%d\t%-15s\t", students[i].id, students[i].name);

            if (students[i].roomNumber == 0) {
                printf("Not assigned\t");
            } else {
                printf("%d\t", students[i].roomNumber);
            }

            if (students[i].rentPaid == 1) {
                printf("Paid\n");
            } else {
                printf("Pending\n");
            }
        }
    }

    printf("\nRoom Status\n");
    printf("-------------------------\n");

    for (i = 0; i < roomCount; i++) {
        if (rooms[i].occupied == 1) {
            printf("Room %d: Occupied by student %d\n", rooms[i].roomNumber, rooms[i].studentId);
        } else {
            printf("Room %d: Available\n", rooms[i].roomNumber);
        }
    }
}

void checkRent(struct Student students[], int studentCount) {
    int id;
    int studentIndex;

    printf("Enter student ID: ");
    id = readInteger();
    studentIndex = findStudent(students, studentCount, id);

    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("Student: %s\n", students[studentIndex].name);
    printf("Monthly rent: Rs. %d\n", MONTHLY_RENT);

    if (students[studentIndex].rentPaid == 1) {
        printf("Rent status: Paid\n");
    } else {
        printf("Rent status: Pending\n");
    }
}

void payRent(struct Student students[], int studentCount) {
    int id;
    int studentIndex;

    printf("Enter student ID: ");
    id = readInteger();
    studentIndex = findStudent(students, studentCount, id);

    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    if (students[studentIndex].rentPaid == 1) {
        printf("Rent has already been marked as paid.\n");
    } else {
        students[studentIndex].rentPaid = 1;
        printf("Rent payment recorded successfully.\n");
    }
}

void vacateRoom(struct Student students[], int studentCount, struct Room rooms[], int roomCount) {
    int id;
    int studentIndex;
    int i;

    printf("Enter student ID: ");
    id = readInteger();
    studentIndex = findStudent(students, studentCount, id);

    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    if (students[studentIndex].roomNumber == 0) {
        printf("This student does not have a room.\n");
        return;
    }

    for (i = 0; i < roomCount; i++) {
        if (rooms[i].roomNumber == students[studentIndex].roomNumber) {
            rooms[i].occupied = 0;
            rooms[i].studentId = 0;
            break;
        }
    }

    printf("Room %d has been vacated.\n", students[studentIndex].roomNumber);
    students[studentIndex].roomNumber = 0;
}

int main(void) {
    struct Student students[MAX_STUDENTS];
    struct Room rooms[MAX_ROOMS];
    int studentCount = 0;
    int roomCount = MAX_ROOMS;
    int choice;
    int i;

    for (i = 0; i < roomCount; i++) {
        rooms[i].roomNumber = 101 + i;
        rooms[i].occupied = 0;
        rooms[i].studentId = 0;
    }

    do {
        printf("\n===== Hostel Management System =====\n");
        printf("1. Add Student\n");
        printf("2. Allocate Room\n");
        printf("3. Display Records\n");
        printf("4. Check Rent Status\n");
        printf("5. Record Rent Payment\n");
        printf("6. Vacate Room\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        choice = readInteger();

        switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                break;
            case 2:
                allocateRoom(students, studentCount, rooms, roomCount);
                break;
            case 3:
                displayRecords(students, studentCount, rooms, roomCount);
                break;
            case 4:
                checkRent(students, studentCount);
                break;
            case 5:
                payRent(students, studentCount);
                break;
            case 6:
                vacateRoom(students, studentCount, rooms, roomCount);
                break;
            case 7:
                printf("Thank you for using Hostel Management System.\n");
                break;
            default:
                printf("Invalid choice. Please select from 1 to 7.\n");
        }
    } while (choice != 7);

    return 0;
}
