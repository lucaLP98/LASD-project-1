#ifndef Library_student_requests_h
#define Library_student_requests_h

#include "library.h"
#include "request_queue.h"
#include "request_tree.h"
#include "student_tree.h"

int menu();
request insertNewRequest();
void operations(const unsigned int task, requestQueue richiesteAttive, requestTree* richiesteSospese, studentTree* studenti, library biblioteca);

#endif
