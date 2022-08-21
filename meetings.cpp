#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "project.h"


inline int compar_int(int a, int b)
{
	if (a < b)
		return -1;
	if (a > b)
		return 1;
	return 0;
}


inline int compar_meeting(const void *meeting0, const void *meeting1)
{
	Meeting *a = (Meeting *)meeting0;
	Meeting *b = (Meeting *)meeting1;

	int months = compar_int(a->date.month, b->date.month);
	if (months != 0)
		return months;

	int days = compar_int(a->date.day, b->date.day);
	if (days != 0)
		return days;

	return compar_int(a->date.hour, b->date.hour);
}


inline void print_calenda(Meeting *calendar, int num)
{
	qsort((void *)calendar, num, sizeof(Meeting), compar_meeting);
	for (int i = 0; i < num; i++) {
		printf("%s %02d.%02d at %02d\n", calendar[i].description,
		       calendar[i].date.day, calendar[i].date.month,
		       calendar[i].date.hour);
	}
}

inline int chec_timeslot(Meeting *calendar, int num, Meeting newmeeting)
{
	for (int i = 0; i < num; i++) {
		if (compar_meeting((void *)&calendar[i],
				    (void *)&newmeeting) == 0) {
			return i;
		}
	}
	return -1;
}


inline int fil_line_count(const char *filename)
{
	FILE *file_ptr = fopen(filename, "r");
	if (!file_ptr)
		return -1;

	int count = 0;
	char buffer[1000];

	while (fgets(buffer, 1000, file_ptr))
		count++;

	fclose(file_ptr);
	return count;
}


inline int validat_date(MeetingDate date)
{
	if (date.month > 12 || date.month < 1) {
		printf("Month cannot be less than 1 or greater than 12.\n");
		return 0;
	}
	if (date.day > 31 || date.day < 1) {
		printf("Day cannot be less than 1 or greater than 31.\n");
		return 0;
	}
	if (date.hour > 23 || date.hour < 0) {
		printf("Hour cannot be negative or greater than 23.\n");
		return 0;
	}
	return 1;
}


inline Meeting *ad_meeting(Meeting *calendar, int num, Meeting newmeeting)
{
	// indicate caller that the meeting timeslot is already taken
	if (chec_timeslot(calendar, num, newmeeting) != -1)
		return NULL;

	calendar = (Meeting *)realloc(calendar, (num + 1) * sizeof(Meeting));
	if (!calendar) {
		printf("ERROR: Could not allocate memory for new calendar!\n");
		exit(1);
	}
	calendar[num] = newmeeting;
	return calendar;
}


inline Meeting *delet_meeting(Meeting *calendar, int num, MeetingDate timeslot)
{
	// a dummy meeting struct to check the calendar against in
	// `check_timeslot`
	Meeting timeslot_dummy;
	timeslot_dummy.date = timeslot;

	int del_i = chec_timeslot(calendar, num, timeslot_dummy);

	// indicate caller that the timeslot to delete was not found
	if (del_i == -1)
		return NULL;

	Meeting *newcalendar = (Meeting *)calloc(num - 1, sizeof(Meeting));
	if (!newcalendar) {
		printf("ERROR: Could not allocate memory for new calendar!\n");
		exit(1);
	}

	for (int i = 0; i < del_i; i++) {
		newcalendar[i] = calendar[i];
	}

	for (int i = del_i; i < num - 1; i++) {
		newcalendar[i] = calendar[i + 1];
	}
	free(calendar);
	return newcalendar;
}

inline int writ_calendar(Meeting *calendar, int num, const char *filename)
{
	char buffer[1000];
	FILE *file_ptr = fopen(filename, "w");
	if (!file_ptr)
		return 1;

	memset(buffer, '\0', 1000);
	for (int i = 0; i < num; i++) {
		snprintf(buffer, 1000, "%s %02d.%02d at %02d\n",
			 calendar[i].description, calendar[i].date.day,
			 calendar[i].date.month, calendar[i].date.hour);
		fputs(buffer, file_ptr);
	}
	if (ferror(file_ptr)) {
		fclose(file_ptr);
		return 1;
	}
	fclose(file_ptr);
	return 0;
}


inline Meeting *lod_calendar(const char *filename)
{
	char buffer[1000];
	FILE *file_ptr = fopen(filename, "r");
	if (!file_ptr)
		return NULL;

	Meeting *calendar = (Meeting *)malloc(sizeof(Meeting));

	memset(buffer, '\0', 1000);
	int i = 0;
	while (fgets(buffer, 1000, file_ptr)) {
		calendar = (Meeting *)realloc(calendar, ++i * sizeof(Meeting));
		sscanf(buffer, "%s %02d.%02d at %02d",
		       calendar[i - 1].description, &calendar[i - 1].date.day,
		       &calendar[i - 1].date.month, &calendar[i - 1].date.hour);
	}
	if (ferror(file_ptr)) {
		fclose(file_ptr);
		return NULL;
	}
	fclose(file_ptr);
	return calendar;
}

inline Command comand_parser()
{
	Command command;
	command.meetingdate.month = 0;
	command.meetingdate.day = 0;
	command.meetingdate.hour = 0;
	command.message = (char *)malloc(sizeof(char));
	if (!command.message) {
		printf("ERROR: Could not allocate memory for new command message!\n");
		exit(1);
	}
	memset(command.message, '\0', 1);

	// setup buffers for each parameter and initialize them
	char type[200], param0[200], param1[200], param2[200], param3[200];
	memset(type, '\0', 200);
	memset(param0, '\0', 200);
	memset(param1, '\0', 200);
	memset(param2, '\0', 200);
	memset(param3, '\0', 200);

	// buffer for the whole line and initialize
	char line[1000];
	memset(line, '\0', 1000);

	// read user input and parse it into each param buffer
	fgets(line, 1000, stdin);
	int num_parsed = 0;
	num_parsed = sscanf(line, "%s %s %s %s %s", type, param0, param1, param2, param3);

	if (strcmp(type, "a") == 0) {
		// A command requires 4 arguments
		if (num_parsed == 5) {
			command.type = a;
			command.message = (char *)realloc(command.message,
							  (strlen(param0) + 1) *
								  sizeof(char));
			if (!command.message) {
				printf("ERROR: Could not allocate memory for new command message!\n");
				exit(1);
			}
			strcpy(command.message, param0);
			sscanf(param1, "%d", &command.meetingdate.month);
			sscanf(param2, "%d", &command.meetingdate.day);
			sscanf(param3, "%d", &command.meetingdate.hour);
			return command;
		} else { // not enough arguments
			command.type = E;
			char *error_msg =
				"a should be followed by exactly 4 arguments.\n";
			command.message = (char *)realloc(
				command.message,
				(strlen(error_msg) + 1) * sizeof(char));
			if (!command.message) {
				printf("ERROR: Could not allocate memory for error message!\n");
				exit(1);
			}
			strcpy(command.message, error_msg);
			return command;
		}
	}
	if (strcmp(type, "b") == 0) {
		// D command requires 3 arguments
		if (num_parsed == 4) {
			command.type = b;
			sscanf(param0, "%d", &command.meetingdate.month);
			sscanf(param1, "%d", &command.meetingdate.day);
			sscanf(param2, "%d", &command.meetingdate.hour);
			return command;
		} else { // not enough arguments
			command.type = E;
			char *error_msg =
				"b should be followed by exactly 3 arguments.\n";
			command.message = (char *)realloc(
				command.message,
				(strlen(error_msg) + 1) * sizeof(char));
			if (!command.message) {
				printf("ERROR: Could not allocate memory for error message!\n");
				exit(1);
			}
			strcpy(command.message, error_msg);
			return command;
		}
	}
	if (strcmp(type, "d") == 0) {
		// W command requires 1 argument
		if (num_parsed == 2) {
			command.type =d;
			command.message = (char *)realloc(command.message,
							  (strlen(param0) + 1) *
								  sizeof(char));
			if (!command.message) {
				printf("ERROR: Could not allocate memory for new command message!\n");
				exit(1);
			}
			strcpy(command.message, param0);
			return command;
		} else { // not enough arguments
			command.type = E;
			char *error_msg =
				"d should be followed by exactly 1 argument.\n";
			command.message = (char *)realloc(
				command.message,
				(strlen(error_msg) + 1) * sizeof(char));
			if (!command.message) {
				printf("ERROR: Could not allocate memory for error message!\n");
				exit(1);
			}
			strcpy(command.message, error_msg);
			return command;
		}
	}
	if (strcmp(type, "e") == 0) {
		// O command requires 1 argument
		if (num_parsed == 2) {
			command.type = e;
			command.message = (char *)realloc(command.message,
							  (strlen(param0) + 1) *
								  sizeof(char));
			if (!command.message) {
				printf("ERROR: Could not allocate memory for new command message!\n");
				exit(1);
			}
			strcpy(command.message, param0);
			return command;
		} else { // not enough arguments
			command.type = E;
			char *error_msg =
				"e should be followed by exactly 1 argument.\n";
			command.message = (char *)realloc(
				command.message,
				(strlen(error_msg) + 1) * sizeof(char));
			if (!command.message) {
				printf("ERROR: Could not allocate memory for error message!\n");
				exit(1);
			}
			strcpy(command.message, error_msg);
			return command;
		}
	}
	if (strcmp(type, "c") == 0) {
		command.type = c;
		return command;
	}
	if (strcmp(type, "f") == 0) {
		command.type = f;
		return command;
	}
	command.type = E;
	char *error_msg = "Invalid command ";
	command.message = (char *)realloc(
		command.message,
		(strlen(error_msg) + strlen(line) + 1) * sizeof(char));
	strcpy(command.message, error_msg);
	strcat(command.message, line);
	return command;
}


inline int meting()
{
    printf(" a: adding a record\t a <description> <month> <day> <hour>\n b: delete meeting \tb <month> <day> <hour>\n c: print calendar \n d: save a calendar to file\t d <filename> \n e: load calendar to file\t e <filename>\n f: quit\n\n\n");
    Meeting *calendar = (Meeting *)calloc(2, sizeof(Meeting));
	if (!calendar) {
		printf("Error: failed to alloc for calendar!");
		return 1;
	}

	Command command;
	Meeting *processed;
	Meeting newmeeting;
	int num = 0;
	do {
		command = comand_parser();
		switch (command.type) {
		case a:
			if (validat_date(command.meetingdate)) {
				newmeeting.date = command.meetingdate;
				memset(newmeeting.description, '\0', 64);
				strcpy(newmeeting.description, command.message);
				processed =
					add_meeting(calendar, num, newmeeting);
				if (!processed) {
					printf("The time slot %02d.%02d at %02d is already allocated.\n",
					       command.meetingdate.day,
					       command.meetingdate.month,
					       command.meetingdate.hour);
					free(command.message);
					break;
				}
				num++;
				printf("SUCCESS\n");
				calendar = processed;
			}
			free(command.message);
			break;
		case b:
			if (validat_date(command.meetingdate)) {
				processed = delete_meeting(calendar, num,
							   command.meetingdate);
				if (!processed) {
					printf("The time slot %02d.%02d at %02d is not in the calendar.\n",
					       command.meetingdate.day,
					       command.meetingdate.month,
					       command.meetingdate.hour);
					free(command.message);
					break;
				}
				num--;
				printf("SUCCESS\n");
				calendar = processed;
			}
			free(command.message);
			break;
		case c:
			print_calenda(calendar, num);
			printf("SUCCESS\n");
			free(command.message);
			break;
		case d:
			if (writ_calendar(calendar, num, command.message)) {
				printf("ERROR: Error while writing a file.\n");
				free(command.message);
				break;
			}
			printf("SUCCESS\n");
			free(command.message);
			break;
		case e:
			processed = lod_calendar(command.message);
			if (!processed) {
				printf("Cannot open file %s for reading.\n",
				       command.message);
				free(command.message);
				break;
			}
			printf("SUCCESS\n");
			num = fil_line_count(command.message);
			free(calendar);
			calendar = processed;
			free(command.message);
			break;
		case f:
			printf("SUCCESS\n");
			free(command.message);
			break;
		case E:
			printf("%s", command.message);
			free(command.message);
			break;
		default:
			printf("ERROR: something went horribly wrong!\n");
			free(command.message);
			break;
		}
	} while (command.type != f);

	free(calendar);
	return 0;
}



