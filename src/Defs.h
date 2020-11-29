#ifndef DEFS_H_
#define DEFS_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum e_bool { false, true } bool;
typedef enum e_status { success, failure } status;

typedef void * Element;
// Hashtable defs
typedef Element(*CopyFunction) (Element);
typedef status(*FreeFunction) (Element);
typedef status(*PrintFunction) (Element);
typedef int(*TransformIntoNumberFunction) (Element);
typedef bool(*EqualFunction) (Element, Element);
// LinkedList defs
/*typedef status(*AppedFunction) (Element);
typedef status(*DeleteFunction) (Element);
typedef status(*GetDataFunction) (Element);
typedef int(*GetLengthFunction) (Element);
typedef Element(*SearchFunction) (Element,Element);
typedef status(*DisplayFunction) (Element);*/



#endif /* DEFS_H_ */
