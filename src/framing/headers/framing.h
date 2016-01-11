#ifndef FRAMING_H_
#define FRAMING_H_

// Output
// return some sort of stream on start ?
void start();
void append(char * c);
void end();

// Input
void set_on_new_frame(callback);
void set_on_error(callback);
void feed(char c);

#endif
