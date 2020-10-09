#include "student_tree.h"

int emptyStudentTree(studentTree t){
    return (t == NULL);
}

studentTree initStudentTree(){
    return NULL;
}

void printStudent(Student s){
    printf("\n Matricola: %s", s.matricola);
    if( !emptyBookTree( s.books ) ){
        printf("\n Libri attualmente presi in prestito:\n");
        inOrderViewBook(s.books, STUDENTE);
    }else{
        printf("\n Nessun libro posseduto dallo studente al momento\n");
    }
}

void inOrderViewStudent(studentTree t){
    if( !emptyStudentTree(t) ){
        inOrderViewStudent(t->sx);
        printStudent(t->student);
        printf("\n"),
        inOrderViewStudent(t->dx);
    }
}

studentTree allocateNewNodeStudent(char newStudent[]){
    studentTree tmp;

    tmp = (studentTree)malloc(sizeof(ABRstudent));
    strcpy(tmp->student.matricola, newStudent);
    tmp->student.books = NULL;
    tmp->sx = NULL;
    tmp->dx = NULL;

    return tmp;
}

studentTree insertNewStudent(studentTree t, char newStudent[], studentTree* newStudentNode){
    if( !emptyStudentTree(t) ){
        if( strcmp(newStudent, t->student.matricola ) < 0 )
            t->sx = insertNewStudent(t->sx, newStudent, newStudentNode);
        else if( strcmp(newStudent, t->student.matricola ) > 0 )
            t->dx = insertNewStudent(t->dx, newStudent, newStudentNode);
    }else{
        t = allocateNewNodeStudent(newStudent);
        *newStudentNode = t;
    }

    return t;
}

studentTree searchStudent(studentTree t, char studentToSearch[]){
    if( !emptyStudentTree(t) ){
    	if( strcmp(studentToSearch, t->student.matricola ) < 0 )
    		return searchStudent( t->sx, studentToSearch );

		if( strcmp(studentToSearch, t->student.matricola ) > 0 )
			return searchStudent( t->dx, studentToSearch );
	}

	return t;
}
