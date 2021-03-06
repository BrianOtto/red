#ifndef LIB_RED_H
#define LIB_RED_H

#include <stdarg.h>
#include <stddef.h>

/* The Red semantic version number components */
#define RED_VERSION_MAJOR 0
#define RED_VERSION_MINOR 6
#define RED_VERSION_PATCH 2

/* A human-friendly string representation of the version */
#define RED_VERSION_STRING "0.6.2"

/*
** A monotonically increasing numeric representation of the version number. Use
** this if you want to do range checks over versions.
*/
#define RED_VERSION_NUMBER (RED_VERSION_MAJOR * 1000000 + \
                             RED_VERSION_MINOR * 1000 + \
                             RED_VERSION_PATCH)

typedef void*     red_value;
typedef red_value red_none;
typedef red_value red_logic;
typedef red_value red_integer;
typedef red_value red_float;
typedef red_value red_string;
typedef red_value red_word;
typedef red_value red_block;
typedef red_value red_path;
typedef red_value red_series;
typedef red_value red_error;

/* Setup and terminate */
void		redOpen();
void		redClose();

/* Run Red code */
red_value	redDo(const char* source);
red_value	redDoBlock(red_block code);
red_value	redCall(red_word name, ...);

/* Expose a C callback in Red */
red_value	redRoutine(red_word name, const char* spec, void* func_ptr);

/* C -> Red */
int			redSymbol(const char* word);
red_none	redNone();
red_logic	redLogic(int logic);
red_integer	redInteger(int number);
red_float	redFloat(double number);
red_string	redString(const char* string);
red_word	redWord(const char* word);
red_block	redBlock(red_value v,...);
red_path	redPath(red_value v, ...);
red_path	redLoadPath(const char* path);
red_value	redMakeSeries(unsigned int type, unsigned int slots);

/* Red -> C */
int			redCInt32(red_integer number);
double		redCDouble(red_float number);
const char*	redCString(red_string string);
int			redTypeOf(red_value value);

/* Red actions */
red_value	redAppend(red_series series, red_value value);
red_value	redChange(red_series series, red_value value);
red_value	redClear(red_series series);
red_value	redCopy(red_series series);
red_value	redFind(red_series series, red_value value);
red_value	redIndex(red_series series);
red_value	redLength(red_series series);
red_value	redMake(red_value proto, red_value spec);
red_value	redPick(red_series series, red_value value);
red_value	redPoke(red_series series, red_value index, red_value value);
red_value	redPut(red_series series, red_value index, red_value value);
red_value	redRemove(red_series series);
red_value	redSelect(red_series series, red_value value);
red_value	redSkip(red_series series, red_integer offset );
red_value	redTo(red_value proto, red_value spec);

/* Access to a Red global word */
red_value	redSet(int id, red_value value);
red_value	redGet(int id);

/* Access to a Red path */
red_value	redSetPath(red_path path, red_value value);
red_value	redGetPath(red_path path);

/* Debugging */
void		redPrint(red_value value);
red_value	redProbe(red_value value);
red_value	redHasError(void);
const char*	redFormError(void);
int			redOpenDebugConsole();
int			redCloseDebugConsole();

/* Red Types */
typedef enum
{
	RED_TYPE_VALUE,
	RED_TYPE_DATATYPE,
	RED_TYPE_UNSET,
	RED_TYPE_NONE,
	RED_TYPE_LOGIC,
	RED_TYPE_BLOCK,
	RED_TYPE_PAREN,
	RED_TYPE_STRING,
	RED_TYPE_FILE,
	RED_TYPE_URL,
	RED_TYPE_CHAR,
	RED_TYPE_INTEGER,
	RED_TYPE_FLOAT,
	RED_TYPE_SYMBOL,
	RED_TYPE_CONTEXT,
	RED_TYPE_WORD,
	RED_TYPE_SET_WORD,
	RED_TYPE_LIT_WORD,
	RED_TYPE_GET_WORD,
	RED_TYPE_REFINEMENT,
	RED_TYPE_ISSUE,
	RED_TYPE_NATIVE,
	RED_TYPE_ACTION,
	RED_TYPE_OP,
	RED_TYPE_FUNCTION,
	RED_TYPE_PATH,
	RED_TYPE_LIT_PATH,
	RED_TYPE_SET_PATH,
	RED_TYPE_GET_PATH,
	RED_TYPE_ROUTINE,
	RED_TYPE_BITSET,
	RED_TYPE_POINT,
	RED_TYPE_OBJECT,
	RED_TYPE_TYPESET,
	RED_TYPE_ERROR,
	RED_TYPE_VECTOR,
	RED_TYPE_HASH,
	RED_TYPE_PAIR,
	RED_TYPE_PERCENT,
	RED_TYPE_TUPLE,
	RED_TYPE_MAP,
	RED_TYPE_BINARY,
	RED_TYPE_SERIES,
	RED_TYPE_TIME,
	RED_TYPE_TAG,
	RED_TYPE_EMAIL,
	RED_TYPE_IMAGE,
	RED_TYPE_EVENT
	// RED_TYPE_CLOSURE,
    // RED_TYPE_PORT
} RedType;

#endif