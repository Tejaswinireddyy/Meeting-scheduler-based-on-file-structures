#ifndef _PROJECT__H_
#define _PROJECT__H_

/** \typedef MeetingDate
 * \brief Meeting date
 *
 */
typedef struct {
	int month; /**< In which month the meeting happens */
	int day; /**< In which day of the month the meeting happens */
	int hour; /**< In which hour of the day the meeting happens */
} MeetingDate;

/** \enum CommandType
 * \brief User command types
 *
 */
enum Commandtype{
	a,	/**< add a new meeting, \ref add_meeting() */
	b,	/**< delete a meeting, \ref delete_meeting() */
	c,	/**< print calendar, \ref print_calendar() */
	d,	/**< save db to file, \ref write_calendar() */
	e,	/**< open db from file */
	f,
	E	/**< quit application */
};

/** \typedef Command
 * \brief User command
 *
 */
typedef struct {
	enum Commandtype type; /**< Which type the command is */
	MeetingDate meetingdate; /**< Useful in \ref A and \ref D command types*/
	char *message; /**< Message containing \ref Meeting.description in \ref A command
	type, or the filename in \ref W and \ref O command types */
} Command;

/** \typedef Meeting
 * \brief One hour meeting
 *
 */
typedef struct {
	MeetingDate date; /**< In which `MeetingDate` the meeting happens */
	char description[64]; /**< Description of the meeting with no whitespace */
} Meeting;

// Documentation for the following functions can be found in `project.c` or in
// the generated doxygen documentation

void print_calendar(Meeting *, int);

Meeting *add_meeting(Meeting *, int, Meeting);

Meeting *delete_meeting(Meeting *, int, MeetingDate);

int write_calendar(Meeting *, int, const char *);

Meeting *load_calendar(const char *);

#endif //! _PROJECT__H_

