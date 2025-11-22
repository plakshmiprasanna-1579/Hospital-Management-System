#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATIENT_FILE "hospital.dat"
#define APPOINT_FILE "appointments.dat"


#define MAX_Name_LEN 100
#define MAX_Gender_LEN 10
#define MAX_Phone_LEN 20
#define MAX_Address_LEN 200
#define MAX_Problem_LEN 200
#define MAX_Doctor_LEN 100
#define MAX_Room_LEN 20
#define MAX_Blood_LEN 10
#define MAX_Emergency_LEN 20
#define MAX_Date_LEN 20
#define MAX_Status_LEN 50

#define MAX_PATIENTS 5000
#define MAX_APPOINTS 5000

typedef struct {
    int id;
    char name[MAX_Name_LEN];
    int age;
    char gender[MAX_Gender_LEN];
    char phone[MAX_Phone_LEN];
    char address[MAX_Address_LEN];
    char problem[MAX_Problem_LEN];
    char doctor[MAX_Doctor_LEN];
    char room[MAX_Room_LEN];
    char blood_group[MAX_Blood_LEN];
    char emergency_contact[MAX_Emergency_LEN];
    char admission_date[MAX_Date_LEN];
    char discharge_date[MAX_Date_LEN];
    char treatment_status[MAX_Status_LEN];
    double bill_amount;
} Patient;
typedef struct {
    int appt_id;
    int patient_id;
    char patient_name[MAX_Name_LEN];
    char doctor[MAX_Doctor_LEN];
    char date[MAX_Date_LEN];
    char time[16];               
    char purpose[MAX_Problem_LEN];
    char status[MAX_Status_LEN];
} Appointment;
// ------------------ FUNCTION DECLARATIONS ------------------
void addPatient();
void viewPatients();
void searchPatient();
void updatePatient();
void deletePatient();
int idExists(int id);
void savePatient(Patient p);
void loadPatients(Patient patients[], int *count);
void writeAllPatients(Patient patients[], int count);

void scheduleAppointment();
void viewAppointments();
void searchAppointment();
void modifyAppointment();
void cancelAppointment();
int appointmentIdExists(int appt_id);
void saveAppointment(Appointment a);
void loadAppointments(Appointment appointments[], int *count);
void writeAllAppointments(Appointment appointments[], int count);
// ------------------ MAIN FUNCTION ------------------
int main() {
    int mainChoice;

    do {
        printf("\n==============================\n");
        printf(" HOSPITAL MANAGEMENT SYSTEM\n");
        printf("==============================\n");
        printf("1. Patient Management\n");
        printf("2. Appointment Management\n");
        printf("3. Exit\n");
        printf("------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &mainChoice);
        getchar();

        switch(mainChoice) {
            case 1: {
                int patientChoice;
                do {
                    printf("\n----- PATIENT MENU -----\n");
                    printf("1. Add New Patient\n");
                    printf("2. View All Patients\n");
                    printf("3. Search Patient by ID\n");
                    printf("4. Update Patient\n");
                    printf("5. Delete Patient\n");
                    printf("6. Back to Main Menu\n");
                    printf("----------------------\n");
                    printf("Enter your choice: ");
                    scanf("%d", &patientChoice);
                    getchar();

                    switch(patientChoice) {
                        case 1: addPatient(); break;
                        case 2: viewPatients(); break;
                        case 3: searchPatient(); break;
                        case 4: updatePatient(); break;
                        case 5: deletePatient(); break;
                        case 6: break;
                        default: printf("Invalid choice!\n");
                    }
                } while(patientChoice != 6);
                break;
            }
            case 2: {
                int appointmentChoice;
                do {
                    printf("\n--- APPOINTMENT MENU ---\n");
                    printf("1. Schedule Appointment\n");
                    printf("2. View All Appointments\n");
                    printf("3. Search Appointment by ID\n");
                    printf("4. Modify Appointment\n");
                    printf("5. Cancel Appointment\n");
                    printf("6. Back to Main Menu\n");
                    printf("-----------------------\n");
                    printf("Enter your choice: ");
                    scanf("%d", &appointmentChoice);
                    getchar();

                    switch(appointmentChoice) {
                        case 1: scheduleAppointment(); break;
                        case 2: viewAppointments(); break;
                        case 3: searchAppointment(); break;
                        case 4: modifyAppointment(); break;
                        case 5: cancelAppointment(); break;
                        case 6: break;
                        default: printf("Invalid choice!\n");
                    }
                } while(appointmentChoice != 6);
                break;
            }
            case 3: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while(mainChoice != 3);

    return 0;
}
void addPatient() {
    Patient p;
    printf("\nEnter Patient ID: ");
    scanf("%d", &p.id);
    getchar();

    if (idExists(p.id)) {
        printf("Error: Patient ID already exists!\n");
        return;
    }

    printf("Enter Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &p.age);
    getchar();

    printf("Enter Gender: ");
    fgets(p.gender, sizeof(p.gender), stdin);
    p.gender[strcspn(p.gender, "\n")] = '\0';

    printf("Enter Phone: ");
    fgets(p.phone, sizeof(p.phone), stdin);
    p.phone[strcspn(p.phone, "\n")] = '\0';

    printf("Enter Address: ");
    fgets(p.address, sizeof(p.address), stdin);
    p.address[strcspn(p.address, "\n")] = '\0';

    printf("Enter problem: ");
    fgets(p.problem, sizeof(p.problem), stdin);
    p.problem[strcspn(p.problem, "\n")] = '\0';

    printf("Enter Doctor: ");
    fgets(p.doctor, sizeof(p.doctor), stdin);
    p.doctor[strcspn(p.doctor, "\n")] = '\0';

    printf("Enter Room: ");
    fgets(p.room, sizeof(p.room), stdin);
    p.room[strcspn(p.room, "\n")] = '\0';

    printf("Enter Blood Group: ");
    fgets(p.blood_group, sizeof(p.blood_group), stdin);
    p.blood_group[strcspn(p.blood_group, "\n")] = '\0';

    printf("Enter Emergency Contact: ");
    fgets(p.emergency_contact, sizeof(p.emergency_contact), stdin);
    p.emergency_contact[strcspn(p.emergency_contact, "\n")] = '\0';

    savePatient(p);
    printf("Patient added successfully!\n");
}
// ------------------ SAVE PATIENT TO FILE ------------------
void savePatient(Patient p) {
    FILE *fp = fopen(PATIENT_FILE, "ab");  
    if (!fp) {
        perror("Error opening file");
        return;
    }
    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);
}
int idExists(int id) {
    FILE *fp = fopen(PATIENT_FILE, "rb");  
    if (!fp) return 0;  

    Patient p;
    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) {
            fclose(fp);
            return 1;  
        }
    }

    fclose(fp);
    return 0;
}  
// ------------------ VIEW ALL PATIENTS ------------------
void viewPatients() {
    FILE *fp = fopen(PATIENT_FILE, "rb");  
    if (!fp) {
        printf("No patient records found.\n");
        return;
    }

    Patient p;
    printf("\n%-5s %-20s %-5s %-10s %-15s %-20s %-20s %-10s %-10s %-15s\n",
           "ID", "Name", "Age", "Gender", "Phone", "Address", "Problem", "Doctor", "Room", "Blood");
    printf("--------------------------------------------------------------------------------\n");

    while (fread(&p, sizeof(Patient), 1, fp)) {
        printf("%-5d %-20s %-5d %-10s %-15s %-20s %-20s %-10s %-10s %-15s\n",
               p.id, p.name, p.age, p.gender, p.phone, p.address, p.problem, p.doctor, p.room, p.blood_group);
    }

    fclose(fp);
}
 // ------------------ SEARCH PATIENT BY ID ------------------
void searchPatient() {
    FILE *fp = fopen(PATIENT_FILE, "rb");
    if(!fp){  
        printf("No patient records found.\n");
        return;
    }

    int id, found = 0;
    Patient p;

    printf("\nEnter Patient ID to search: ");
    scanf("%d", &id);
    getchar(); 

    while (fread(&p, sizeof(Patient), 1, fp)) {
        if (p.id == id) {
            printf("\nPatient Found:\n");
            printf("ID: %d\n", p.id);
            printf("Name: %s\n", p.name);
            printf("Age: %d\n", p.age);
            printf("Gender: %s\n", p.gender);
            printf("Phone: %s\n", p.phone);
            printf("Address: %s\n", p.address);
            printf("Problem: %s\n", p.problem);
            printf("Doctor: %s\n", p.doctor);
            printf("Room: %s\n", p.room);
            printf("Blood Group: %s\n", p.blood_group);
            printf("Emergency Contact: %s\n", p.emergency_contact);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No patient found with ID %d.\n", id);
    }

    fclose(fp);
} 
void updatePatient() {
    Patient patients[100];
    int count = 0, id, found = 0;
    loadPatients(patients, &count);

    printf("Enter Patient ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            found = 1;

            printf("Enter new Name: ");
            fgets(patients[i].name, sizeof(patients[i].name), stdin);
            patients[i].name[strcspn(patients[i].name, "\n")] = '\0';

            printf("Enter new Age: ");
            scanf("%d", &patients[i].age);
            getchar();

            printf("Enter new Phone: ");
            fgets(patients[i].phone, sizeof(patients[i].phone), stdin);
            patients[i].phone[strcspn(patients[i].phone, "\n")] = '\0';

            printf("Enter new Address: ");
            fgets(patients[i].address, sizeof(patients[i].address), stdin);
            patients[i].address[strcspn(patients[i].address, "\n")] = '\0';

            printf("Enter new Problem: ");
            fgets(patients[i].problem, sizeof(patients[i].problem), stdin);
            patients[i].problem[strcspn(patients[i].problem, "\n")] = '\0';

            printf("Enter new Doctor: ");
            fgets(patients[i].doctor, sizeof(patients[i].doctor), stdin);
            patients[i].doctor[strcspn(patients[i].doctor, "\n")] = '\0';

            printf("Enter new Room: ");
            fgets(patients[i].room, sizeof(patients[i].room), stdin);
            patients[i].room[strcspn(patients[i].room, "\n")] = '\0';

            printf("Enter new Blood Group: ");
            fgets(patients[i].blood_group, sizeof(patients[i].blood_group), stdin);
            patients[i].blood_group[strcspn(patients[i].blood_group, "\n")] = '\0';

            printf("Enter new Emergency Contact: ");
            fgets(patients[i].emergency_contact, sizeof(patients[i].emergency_contact), stdin);
            patients[i].emergency_contact[strcspn(patients[i].emergency_contact, "\n")] = '\0';

            break;
        }
    }

    if (found) {
        writeAllPatients(patients, count);
        printf("Patient record updated successfully.\n");
    } else {
        printf("Patient ID %d not found.\n", id);
    }
}
void deletePatient() {
    Patient patients[100];
    int count = 0, id, found = 0;
    loadPatients(patients, &count);

    printf("Enter Patient ID to delete: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            found = 1;
            printf("Are you sure you want to delete %s (ID %d)? (y/n): ", patients[i].name, id);
            char confirm = getchar();
            getchar();
            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < count - 1; j++) patients[j] = patients[j+1];
                count--;
                writeAllPatients(patients, count);
                printf("Patient deleted successfully.\n");
            } else {
                printf("Deletion cancelled.\n");
            }
            break;
        }
    }

    if (!found) printf("Patient ID %d not found.\n", id);
}
void loadPatients(Patient patients[], int *count) {
    FILE *fp = fopen(PATIENT_FILE, "rb");
    if (!fp) { *count = 0; return; }
    *count = 0;
    while(fread(&patients[*count], sizeof(Patient), 1, fp)) (*count)++;
    fclose(fp);
}

void writeAllPatients(Patient patients[], int count) {
    FILE *fp = fopen(PATIENT_FILE, "wb");
    if (!fp) { perror("Error saving patients"); return; }
    fwrite(patients, sizeof(Patient), count, fp);
    fclose(fp);
}
/* ------------------ APPOINTMENT MODULE (added) ------------------ */

void saveAppointment(Appointment a) {
    FILE *fp = fopen(APPOINT_FILE, "ab");
    if (!fp) {
        perror("Error opening appointment file");
        return;
    }
    fwrite(&a, sizeof(Appointment), 1, fp);
    fclose(fp);
}

int appointmentIdExists(int appt_id) {
    FILE *fp = fopen(APPOINT_FILE, "rb");
    if (!fp) return 0;

    Appointment a;
    while (fread(&a, sizeof(Appointment), 1, fp)) {
        if (a.appt_id == appt_id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void scheduleAppointment() {
    Appointment a;

    printf("\nEnter Appointment ID: ");
    scanf("%d", &a.appt_id);
    getchar();

    if (appointmentIdExists(a.appt_id)) {
        printf("Error: Appointment ID already exists!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &a.patient_id);
    getchar();

    printf("Enter Patient Name: ");
    fgets(a.patient_name, sizeof(a.patient_name), stdin);
    a.patient_name[strcspn(a.patient_name, "\n")] = '\0';

    printf("Enter Doctor: ");
    fgets(a.doctor, sizeof(a.doctor), stdin);
    a.doctor[strcspn(a.doctor, "\n")] = '\0';

    printf("Enter Date (DD-MM-YYYY): ");
    fgets(a.date, sizeof(a.date), stdin);
    a.date[strcspn(a.date, "\n")] = '\0';

    printf("Enter Time: ");
    fgets(a.time, sizeof(a.time), stdin);
    a.time[strcspn(a.time, "\n")] = '\0';

    printf("Enter Purpose: ");
    fgets(a.purpose, sizeof(a.purpose), stdin);
    a.purpose[strcspn(a.purpose, "\n")] = '\0';

    printf("Enter Status: ");
    fgets(a.status, sizeof(a.status), stdin);
    a.status[strcspn(a.status, "\n")] = '\0';

    saveAppointment(a);
    printf("Appointment scheduled successfully!\n");
}

void viewAppointments() {
    FILE *fp = fopen(APPOINT_FILE, "rb");
    if (!fp) {
        printf("No appointments found.\n");
        return;
    }

    Appointment a;

    printf("\n%-10s %-10s %-20s %-20s %-12s %-8s %-15s\n",
           "ApptID", "PatID", "Patient Name", "Doctor", "Date", "Time", "Status");
    printf("-------------------------------------------------------------------------------\n");

    while (fread(&a, sizeof(Appointment), 1, fp)) {
        printf("%-10d %-10d %-20s %-20s %-12s %-8s %-15s\n",
               a.appt_id, a.patient_id, a.patient_name, a.doctor, a.date, a.time, a.status);
    }

    fclose(fp);
}

void searchAppointment() {
    FILE *fp = fopen(APPOINT_FILE, "rb");
    if (!fp) {
        printf("No appointment records found.\n");
        return;
    }

    int appt_id, found = 0;
    Appointment a;

    printf("\nEnter Appointment ID to search: ");
    scanf("%d", &appt_id);
    getchar();

    while (fread(&a, sizeof(Appointment), 1, fp)) {
        if (a.appt_id == appt_id) {
            printf("\nAppointment Found:\n");
            printf("Appointment ID: %d\n", a.appt_id);
            printf("Patient ID: %d\n", a.patient_id);
            printf("Patient Name: %s\n", a.patient_name);
            printf("Doctor: %s\n", a.doctor);
            printf("Date: %s\n", a.date);
            printf("Time: %s\n", a.time);
            printf("Purpose: %s\n", a.purpose);
            printf("Status: %s\n", a.status);
            found = 1;
            break;
        }
    }

    if (!found) printf("Appointment not found!\n");

    fclose(fp);
}

void modifyAppointment() {
    Appointment appointments[100];
    int count = 0, appt_id, found = 0;
    loadAppointments(appointments, &count);

    printf("Enter Appointment ID to modify: ");
    scanf("%d", &appt_id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (appointments[i].appt_id == appt_id) {
            found = 1;

            printf("Enter new Date: ");
            fgets(appointments[i].date, sizeof(appointments[i].date), stdin);
            appointments[i].date[strcspn(appointments[i].date, "\n")] = '\0';

            printf("Enter new Time: ");
            fgets(appointments[i].time, sizeof(appointments[i].time), stdin);
            appointments[i].time[strcspn(appointments[i].time, "\n")] = '\0';

            printf("Enter new Status: ");
            fgets(appointments[i].status, sizeof(appointments[i].status), stdin);
            appointments[i].status[strcspn(appointments[i].status, "\n")] = '\0';

            break;
        }
    }

    if (found) {
        writeAllAppointments(appointments, count);
        printf("Appointment updated.\n");
    } else {
        printf("Appointment ID not found.\n");
    }
}

void cancelAppointment() {
    Appointment appointments[100];
    int count = 0, appt_id, found = 0;
    loadAppointments(appointments, &count);

    printf("Enter Appointment ID to cancel: ");
    scanf("%d", &appt_id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (appointments[i].appt_id == appt_id) {
            found = 1;

            for (int j = i; j < count - 1; j++)
                appointments[j] = appointments[j + 1];

            count--;
            writeAllAppointments(appointments, count);
            printf("Appointment cancelled.\n");
            break;
        }
    }

    if (!found) printf("Appointment ID not found.\n");
}

void loadAppointments(Appointment appointments[], int *count) {
    FILE *fp = fopen(APPOINT_FILE, "rb");
    if (!fp) { *count = 0; return; }

    *count = 0;
    while (fread(&appointments[*count], sizeof(Appointment), 1, fp))
        (*count)++;

    fclose(fp);
}

void writeAllAppointments(Appointment appointments[], int count) {
    FILE *fp = fopen(APPOINT_FILE, "wb");
    if (!fp) { perror("Error saving appointments"); return; }

    fwrite(appointments, sizeof(Appointment), count, fp);
    fclose(fp);
}