#ifndef EVENT_H
#define EVENT_H

int loop;

/**
 * signal handler
 * 
 * @param int type of signal
 * 
 **/
void sighandler(int);


/**
 * emit a event
 * 
 * @param int file
 * @param int event type
 * @param int event code
 * @param int event val
 * 
 **/
void emit(int file, int type, int code, int val);


#endif