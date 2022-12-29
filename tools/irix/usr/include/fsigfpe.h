C 
C  Copyright 1992 Silicon Graphics,  Inc.
C  ALL RIGHTS RESERVED
C  
C  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
C  The copyright notice above does not evidence any  actual  or
C  intended  publication of this source code and material is an
C  unpublished work by Silicon  Graphics,  Inc.  This  material
C  contains CONFIDENTIAL INFORMATION that is the property and a
C  trade secret of Silicon Graphics, Inc. Any use,  duplication
C  or  disclosure  not  specifically  authorized  in writing by
C  Silicon Graphics is  strictly  prohibited.  THE  RECEIPT  OR
C  POSSESSION  OF  THIS SOURCE CODE AND/OR INFORMATION DOES NOT
C  CONVEY ANY RIGHTS TO REPRODUCE, DISCLOSE OR  DISTRIBUTE  ITS
C  CONTENTS,  OR  TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT
C  MAY DESCRIBE, IN WHOLE OR IN PART.
C  
C  U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND
C  Use, duplication or disclosure by the Government is  subject
C  to  restrictions  as  set  forth  in  FAR 52.227.19(c)(2) or
C  subparagraph (c)(1)(ii) of the Rights in Technical Data  and
C  Computer  Software  clause  at  DFARS 252.227-7013 and/or in
C  similar or successor clauses in the FAR, or the DOD or  NASA
C  FAR  Supplement.  Unpublished  --  rights reserved under the
C  Copyright Laws of the United States. Contractor/manufacturer
C  is Silicon Graphics, Inc., 2011 N. Shoreline Blvd., Mountain
C  View, CA 94039-7311
C
C
C	fsigfpe.h - constants and data areas for the floating-point
C	exception-handling package when FORTRAN is the native language. 
C
C	The MIPS floating-point accelerator may raise floating-point exceptions
C	due to five conditions:
C	FPE_OVERFL (overflow), FPE_UNDERFL (underflow), FPE_DIVZERO
C	(divide-by-zero), FPE_INEXACT (inexact result), or FPE_INVALID 
C	(invalid operand, e.g. infinity). 
C
C	Usually these conditions are masked and do not cause a floating-point
C	exception; instead, a default value is substituted for the result of
C	the operation and the program continues silently.  This event may be
C	intercepted by causing an exception to be raised.  Once an exception
C	is raised, the specific conditions which caused the exception may be 
C	determined, and more appropriate action taken.  This package provides a
C	mechanism for 'handling' such exceptions, classifying them by the 
C	conditions which caused them, and substituting a value, either a default
C	value or one supplied by the user.  This package also includes mechanisms
C	useful in debugging code that causes traps : stack trace, trap counts, 
C	abort and exit functions.  This package is provided for all of the above
C	conditions except FPE_INEXACT.  Two options exist to initiate trap 
C	handling:  the programmable interface, and the environment variable 
C	(runtime) interface.
C
C        *********************************************************************
C       The Runtime interface:
C
C       Link time switch -lfpe:
C	In order to acquire the trap handler runtime interface, link the program
C	with the switch -lfpe.   Traps will then be handled according to the
C       runtime environment variable TRAP_FPE.
C
C      TRAP_FPE:
C	This runtime environment variable specifies how the enabled trap handler
C	shall behave.  If TRAP_FPE is undefined, the program will execute with
C	sgi defaults (as found in the default values of sigfpe: 
C	array fsigfpe().repls; see below).  To execute user routine as if it 
C	were not compiled -lfpe, use TRAP_FPE=OFF
C
C      Syntax:
C
C	The string "TRAP_FPE" will be checked as an environment variable, in
C	upper case letters only.  The string defining the actions of the trap 
C	handler can be in either upper case, or lower case for the user's 
C	convenience.
C
C	The TRAP_FPE variable can take one of two forms:  either a "global"
C	value, or a list of individual items.  The two forms cannot be combined.
C	The global form is given by:
C
C	setenv TRAP_FPE global_value
C
C	where global_value takes on one of the following values:
C
C		"" or OFF
C					Execute the program with no trap handling 
C					enabled.  Same as linking WITHOUT -lfpe.
C					Same as TRAP_FPE undefined.
C		ON
C					Same as TRAP_FPE="ALL=DEFAULT".
C
C	Alternately, replacement values and actions may be specified for
C	each of the possible trap types individually. This is accomplished by:
C
C	setenv TRAP_FPE  "item;item;item...."
C
C					TRAP_FPE is set to a list of items. 
C					The length of this is limited by csh.
C
C		an item can be one of the following:

C			traptype=statuslist
C					where traptype defines the specific
C					floating point exception to enable,
C					and statuslist defines the list of
C					actions upon encountering the trap.
C			DEBUG
C					confirm the parsing of the environment
C					variable and the trap settings.
C
C
C		trap type can be one of the following literal strings:
C
C			UNDERFL		underflow
C
C			OVERFL		overflow
C
C			DIVZERO		divide by zero	
C
C			INVALID		invalid operand
C
C			ALL		all of the above
C
C		statuslist is a list separated by commas.  It contains an 
C		optional symbolic replacement value and an optional list of
C		actions.
C
C		replacement values:
C
C			DEFAULT		Use the predefined SGI default
C					(from sigfpe, fsigfpe().repls)
C					as the return result, and continue
C					execution.  If no other replacement
C					value is specified, this is the
C					default.
C			
C			APPROPRIATE	Use IEEE standard results as the return
C					result for FPE_OVERFL, FPE_DIVZERO, and
C					FPE_INVALID exceptions.  Use FPE_ZERO
C					for FPE_UNDERFL exceptions.
C
C			ZERO		substitute FPE_ZERO as the return result.
C
C			MIN		substitute FPE_MIN as the return result.
C
C			MAX		substitute FPE_MIN as the return result.
C
C			INF		substitute FPE_INF as the return result.
C
C			NAN		substitute FPE_NAN as the return result.
C
C			FLUSH_ZERO	set the flush to zero bit in the Control 
C					Status Register.  Causes flush to zero 
C					without invoking the trap handler.  Works
C					only for underflow on the R4000 and later
C					processors.  Works like ZERO for the R3000.
C				
C		actions:  COUNT(n)
C					A count of the trap type will be printed 
C					to stderr at the end of execution of the 
C					program, and every nth trap. 
C			
C		These actions take an optional integer in parentheses:
C
C			ABORT(n)	Core dump and abort program upon encountering
C					the nth trap, default is 1.
C
C			EXIT(n)		Exit program without coredump upon encountering
C					the nth trap, default is 1.
C
C			TRACE(n)	If trap is encountered, print a stack trace to 
C					stderr. Print this stack trace up to n times.
C					Default	is 10.
C
C       Example:
C
C		setenv TRAP_FPE "ALL=COUNT;UNDERFLOW=ZERO;OVERFLOW=APPROPRIATE,
C		TRACE(5),ABORT(100); DIVZERO=ABORT"
C
C	count all traps, print final results (even on abort) to stderr,
C	underflow to zero, overflow to IEEE, trace first five overflows, if
C	100 overflows occur then abort, abort on first zero divide.
C
C        *********************************************************************
C	The programmable interface:
C	Control is initiated (and canceled) by calling the function handle_sigfpes.
C	The function takes four arguments:
C
C		handle_sigfpes(onoff, en_mask, user_routine,
C			abort_action, abort_routine)
C
C		   onoff - a flag indicating whether handling is 
C			being turned on (onoff == FPE_ON) or 
C			debug (onoff = FPE_DEBUG)
C			off (onoff != FPE_ON && onoff != FPE_DEBUG)
C	
C		   The remaining parameters are only valid if onoff == FPE_ON
C		   or FPE_DEBUG.
C
C		   en_mask - indicates which of the four conditions should
C			raise a floating-point exception.  This parameter
C			is only valid if onoff == FPE_ON or FPE_DEBUG, and is
C			the sum of FPE_EN_UNDERFL, FPE_EN_OVERFL, FPE_EN_DIVZERO,
C			and FPE_EN_INVALID
C
C		   user_routine - The address of a user's routine which
C			is called to set the value.  This routine is called
C			if the replacement value code for the condition-at-hand
C			is FPE_USER_DETERMINED (see below). It
C			is invoked with the following parameters:
C
C			user_routine(exception, val)
C			integer *4 exception(0:4)
C			integer *4 val(2)
C
C			The exception array contains useful information
C			concerning the exception.  Its elements are
C			FPE_EXCEPTION_TYPE (0), FPE_INVALID_ACTION (1),
C			FPE_INVALID_TYPE (2), FPE_VALUE_TYPE (3), and
C			FPE_VALUE_SIGN (4):
C	
C			FPE_EXCEPTION_TYPE : FPE_OVERFL, FPE_UNDERFL, etc.

C			FPE_INVALID_ACTION : FPE_SET_RESULT if result is being
C				set; FPE_REPL_OPERAND if operand is being
C				replaced.

C			FPE_INVALID_TYPE: if exception_type is FPE_INVALID, this
C				indicates the type of FPE_INVALID
C				exception which occurred: 
C				FPE_CVTW_OVERFL, FPE_ZERO_TIMES_INF, etc.

C			FPE_VALUE_TYPE: FPE_SINGLE, FPE_DOUBLE, or FPE_WORD

C			FPE_VALUE_SIGN: The suggested sign for the value, 
C				based on an analysis of the instruction:
C				FPE_NEGATIVE or FPE_POSITIVE

C			val: an array in which the modified value should
C				be placed.  If an operand is being replaced,
C				val has a copy of the current operand.
C	
C		   abort_action - If the handler encounters an unexpected 
C			condition, an inconsistency, or begins looping, 
C			this flag indicates what action should be taken.  The 
C			possible values are:
C	
C				FPE_TURN_OFF_HANDLER_ON_ERROR - instruct the 
C					floating-point-accelerator to cease
C					causing exceptions and continue.
C					(i.e., disable handling)
C
C				FPE_ABORT_ON_ERROR - kill the process after 
C					giving an error message and possibly 
C					calling a user-supplied cleanup routine.
C
C				FPE_REPLACE_HANDLER_ON_ERROR - install the 
C					indicated user routine as the handler
C					when such an error is encountered.
C					Future floating-point exceptions will
C					branch to the user-routine. 
C					(see signal(2))
C
C				FPE_USER_HANDLER - install the indicated user 
C					routine as the handler.  (see signal(2))
C	
C		    abort_routine - When a fatal error (i.e., one described
C			under 'abort_action' above) is encountered, this
C			argument is used as the address of a user routine.  
C			If abort_action is FPE_ABORT_ON_ERROR, and this argument
C			is non-zero, it is used as the address of a routine
C			to call before aborting.  The routine is invoked
C			with a single argument - the pc of the exception.
C
C			If abort_action is FPE_REPLACE_HANDLER_ON_ERROR, or
C			FPE_USER_HANDLER, and abort_routine is non-zero, it 
C			will be installed as the floating point exception
C			handler.  In the former case, the instruction which
C			caused the unexpected exception will be re-executed, 
C			causing a new exception, and abort_routine entered.
C			(see signal(2)).
C
C			If abort_action is _ABORT_ON_ERROR, then abort_routine
C			is invoked with the following parameter:
C
C			abort_routine( pc )
C			integer *4 pc
C
C			For mips3 and later processors, program counters are
C			8 bytes in length, and then abort_routine should be
C			invoked with the following parameter:
C
C			abort_routine( pc )
C			integer *8 pc
C
C			pc is the program counter of the instruction
C			which caused the exception (pc + 4, if the
C			instruction is in a branch delay slot).
C
C			If abort_action is _REPLACE_HANDLER_ON_ERROR or
C			FPE_USER_HANDLER (i.e. abort_routine is actually a
C			floating point exception handler), then abort_routine
C			is invoked with the following parameters:
C
C			int abort_routine( sig, code, sc )
C			int sig, code;
C			struct sigcontext *sc;
C
C			See signal(5) and /usr/include/sigfpe.h for more
C			information on user-defined floating point exception
C			handlers.
C

	



 	integer*4  FPE_OFF   
	parameter ( FPE_OFF = 0)
 	integer*4  FPE_ON   
	parameter ( FPE_ON = 1)
 	integer*4  FPE_DEBUG
	parameter ( FPE_DEBUG = 2)
	
 	integer*4  FPE_ABORT_ON_ERROR   
	parameter ( FPE_ABORT_ON_ERROR = 0)
 	integer*4  FPE_TURN_OFF_HANDLER_ON_ERROR   
	parameter ( FPE_TURN_OFF_HANDLER_ON_ERROR = 1)
 	integer*4  FPE_REPLACE_HANDLER_ON_ERROR   
	parameter ( FPE_REPLACE_HANDLER_ON_ERROR = 2)
 	integer*4  FPE_USER_HANDLER   
	parameter ( FPE_USER_HANDLER = 3)
	
C  	exceptions 	

 	integer*4  FPE_UNDERFL   
	parameter ( FPE_UNDERFL = 1)
 	integer*4  FPE_OVERFL    
	parameter ( FPE_OVERFL = 2)
 	integer*4  FPE_DIVZERO   
	parameter ( FPE_DIVZERO = 3)
 	integer*4  FPE_INVALID   
	parameter ( FPE_INVALID = 4)
 	integer*4  FPE_INT_OVERFL   
	parameter ( FPE_INT_OVERFL = 5)
 	integer*4  FPE_N_EXCEPTION_TYPES   
	parameter ( FPE_N_EXCEPTION_TYPES = 5)
	
 	integer*4  FPE_EN_UNDERFL   
	parameter ( FPE_EN_UNDERFL = 2)
 	integer*4  FPE_EN_OVERFL    
	parameter ( FPE_EN_OVERFL = 4)
 	integer*4  FPE_EN_DIVZERO   
	parameter ( FPE_EN_DIVZERO = 8)
 	integer*4  FPE_EN_INVALID   
	parameter ( FPE_EN_INVALID = 16)
 	integer*4  FPE_EN_INT_OVERFL   
	parameter ( FPE_EN_INT_OVERFL = 32)

C  types 

 	integer*4  FPE_SINGLE   
	parameter ( FPE_SINGLE = 0)
 	integer*4  FPE_DOUBLE   
	parameter ( FPE_DOUBLE = 1)
 	integer*4  FPE_WORD      
	parameter ( FPE_WORD = 2)
 	integer*4  FPE_LONGWORD      
	parameter ( FPE_LONGWORD = 3)
 	integer*4  FPE_FIRST_TYPE   
	parameter ( FPE_FIRST_TYPE = FPE_SINGLE )
 	integer*4  FPE_LAST_TYPE   
	parameter ( FPE_LAST_TYPE = FPE_LONGWORD )

	
C  signs 

 	integer*4  FPE_POSITIVE   
	parameter ( FPE_POSITIVE = 0)
 	integer*4  FPE_NEGATIVE   
	parameter ( FPE_NEGATIVE = 1)

	
C  actions  

 	integer*4  FPE_SET_RESULT   
	parameter ( FPE_SET_RESULT = 0)
 	integer*4  FPE_REPL_OPERAND   
	parameter ( FPE_REPL_OPERAND = 1)
 	integer*4  FPE_REPL_RS   
	parameter ( FPE_REPL_RS = 1)
 	integer*4  FPE_REPL_RT   
	parameter ( FPE_REPL_RT = 2)

	
C  elements of exception array 

 	integer*4  FPE_EXCEPTION_TYPE   
	parameter ( FPE_EXCEPTION_TYPE = 0)
 	integer*4  FPE_INVALID_ACTION   
	parameter ( FPE_INVALID_ACTION = 1)
 	integer*4  FPE_INVALID_TYPE     
	parameter ( FPE_INVALID_TYPE = 2)
 	integer*4  FPE_VALUE_TYPE       
	parameter ( FPE_VALUE_TYPE = 3)
 	integer*4  FPE_VALUE_SIGN       
	parameter ( FPE_VALUE_SIGN = 4)

	

C	When an exception is encountered, the handler examines the instruction
C	causing the exception and the state of the floating-point accelerator
C	to determine the correct action to take, and the program is continued.
C	In most cases of floating-point exceptions, e.g.  FPE_UNDERFL, FPE_OVERFL, 
C	FPE_DIVZERO, and some instances of FPE_INVALID, an appropriate value is 
C	substituted for the result of the operation, and the instruction 
C	which caused the exception is skipped.  For most exceptions arising 
C	due to an invalid operand (FPE_INVALID exceptions), more meaningful 
C	behavior may be obtained by replacing an erroneous operand.  In this
C	case, the operand is replaced, and the instruction re-issued.
C	
C	For exceptions which always warrant the setting of the result, the
C	value used is determined by the exception type (FPE_UNDERFL, FPE_OVERFL,
C	or FPE_DIVZERO).
C
C	These default values may be overridden by initializing a common block 
C	named 'sigfpe'.  A declaration for this common block is below.  
C	It has a single member, the array 'fsigfpe'.  
C	Each element in fsigfpe().repls is interpreted as an integer code used to 
C	select one of a set of replacement values, or the code FPE_USER_DETERMINED,
C	which indicates that the user's routine should be invoked to provide the 
C	replacement value.  If the code is not FPE_USER_DETERMINED, the appropriately-
C	typed (single- or double- precision) and appropriately-signed replacement 
C	value is then substituted in the operation causing the exception.  The
C	integer codes, and the corresponding replacement values they select, are 
C	listed below:
C
C		FPE_ZERO  - use zero as the replacement value.
C
C		FPE_MIN   - use the appropriately-typed minimum value as 
C			    the replacement. (i.e., the smallest number
C			    which is representable in that format)
C
C		FPE_MAX   - use the appropriately-typed maximum value as 
C			    the replacement.
C
C		FPE_INF   - use the appropriately-typed value for infinity 
C			    as the replacement.
C
C		FPE _NAN  - use the appropriately-typed value for not-a-number 
C			    as the replacement.
C
C		FPE_APPROPRIATE - use a handler-supplied appropriate value 
C			    as the replacement.  These are _ZERO for _UNDERFL,
C			    and values which will produce the IEEE result the
C			    instruction would have produced if it had not been
C			    trapped.
C
C		FPE_USER_DETERMINED - call the user's routine to set the value.
C
C		FPE_NEG   - use the negative of the original argument (valid
C			    only for cases FPE_SQRT_NEG_X and FPE_RSQRT_NEG_X
C			    (see below)
C
C		FPE_FLUSH_ZERO 	- set the flush to zero bit in the Control Status
C			    Register.  Causes flush to zero without invoking
C			    the trap handler.  Works only for underflow traps
C			    on the R4000 and later processors.  Works like 
C			    FPE_ZERO for the R3000.
C				
C
C	
C	If the replacement-value code for FPE_INVALID exceptions is FPE_USER_DETERMINED,
C	the replacement value for all FPE_INVALID exceptions will be obtained from 
C	the user_routine.  Otherwise, the code for FPE_INVALID is ignored, as this 
C	exception has cases which warrant the replacement of an operand as well
C	as cases which warrant the setting of the result (see below).
C	
C	
C	The elements of this array of structures are interpreted as follows:
C
C		fsigfpe(0) is ignored.
C		fsigfpe(1) is the structure for  FPE_UNDERFL 
C		fsigfpe(2) is the structure for  FPE_OVERFL 
C		fsigfpe(3) is the structure for  FPE_DIVZERO 
C		fsigfpe(4) is the structure for  FPE_INVALID  
C
C	Each structure contains the following:
C
C		structure /sigfpe_template/
C		      integer*4 repls			The replacement code
C		      integer*4 count			The count limit
C		      integer*4 trace			The trace limit
C		      integer*4 abort			The abort limit
C		      integer*4 exit 			The exit limit
C		end structure
C
C	Each limit defines the number of traps that will be executed before the 
C	defined action occurs:
C
C	count : print a count of all the traps that have count enabled.
C	trace : print a dbx stack trace. 
C	abort : abort with a core dump.
C	exit  : exit program, no core dump.
C
C
C	If no sigfpe common block is initialized, no count, trace, exit or 
C	abort actions will be performed.  The default values are used as if 
C	the following initialization had been performed:
C
C	data fsigfpe.repls / 0,  FPE_ZERO,  FPE_APPROPRIATE,  FPE_APPROPRIATE,  0  /
C
C	Thus, the default replacement code for FPE_UNDERFL is FPE_ZERO, for 
C	FPE_OVERFL is FPE_APPROPRIATE, etc.  Default replacement codes for 
C	FPE_INVALID are determined from common blocks invalidop_results and
C	invalidop_operands (see below).
C
C
C  the possible replacement values:  FPE_ZERO = 0, FPE_MIN = minimum valid number, etc. 


 	integer*4  FPE_ZERO   
	parameter ( FPE_ZERO = 1)
 	integer*4  FPE_MIN   
	parameter ( FPE_MIN = 2)
 	integer*4  FPE_MAX   
	parameter ( FPE_MAX = 3)
 	integer*4  FPE_INF   
	parameter ( FPE_INF = 4)
 	integer*4  FPE_NAN   
	parameter ( FPE_NAN = 5)
 	integer*4  FPE_FLUSH_ZERO
	parameter ( FPE_FLUSH_ZERO = 6)
 	integer*4  FPE_APPROPRIATE   
	parameter ( FPE_APPROPRIATE = 7)
 	integer*4  FPE_USER_DETERMINED   
	parameter ( FPE_USER_DETERMINED = 8)
 	integer*4  FPE_NEG   
	parameter ( FPE_NEG = 9)
 	integer*4  FPE_MIN_REPL   
	parameter ( FPE_MIN_REPL = FPE_ZERO )
 	integer*4  FPE_MAX_REPL   
	parameter ( FPE_MAX_REPL = FPE_NEG )


	structure /sigfpe_template/
	      integer*4 repls
	      integer*4 count
	      integer*4 trace
	      integer*4 abort
	      integer*4 exit 
	end structure

	record /sigfpe_template/ fsigfpe (0: FPE_N_EXCEPTION_TYPES )

	common /sigfpe / fsigfpe

C	For  FPE_INVALID  exceptions, the correct action may be either to
C	set the result and skip the instruction, or to replace an
C	operand and retry the instruction.  

C	There are four cases in which the result is set.  The common 
C	block named 'invalidop_results' is consulted for user-initialized
C	codes for these cases.  A declaration for this common block,
C	which contains only the array 'invres', is below.  Each element 
C	governs the following cases:
	
C	---index---
C	#  mnemonic			exception condition
C	--------------------------------------------------------------
C	0  (none)			(ignored)
C	1   FPE_MAGNITUDE_INF_SUBTRACTION subtraction of infinities: 
C	2   FPE_ZERO_TIMES_INF 	        multiplication 0 * infinity
C	3   FPE_ZERO_DIV_ZERO 	        0/0
C	4   FPE_INF_DIV_INF 		infinity / infinity

C		if the corresponding code in the array is  FPE_APPROPRIATE ,
C		uninitialized, or not a legal value, the result used is
	
C		for  FPE_MAGNITUDE_INF_SUBTRACTION  -  FPE_NAN
C		for  FPE_ZERO_TIMES_INF 	    -  FPE_NAN
C		for  FPE_ZERO_DIV_ZERO 		    -  FPE_NAN
C		for  FPE_INF_DIV_INF 		    -  FPE_NAN
	
C  invalid ops for which the result is set  

 	integer*4  FPE_MAGNITUDE_INF_SUBTRACTION   
	parameter ( FPE_MAGNITUDE_INF_SUBTRACTION = 1)
 	integer*4  FPE_ZERO_TIMES_INF  	 
	parameter ( FPE_ZERO_TIMES_INF = 2)
 	integer*4  FPE_ZERO_DIV_ZERO   	 
	parameter ( FPE_ZERO_DIV_ZERO = 3)
 	integer*4  FPE_INF_DIV_INF     	 
	parameter ( FPE_INF_DIV_INF = 4)

#if (_MIPS_SIM == _ABIO32)

 	integer*4  FPE_N_INVALIDOP_RESULTS   
	parameter ( FPE_N_INVALIDOP_RESULTS = 4)
#else
 	integer*4  FPE_N_INVALIDOP_RESULTS   
	parameter ( FPE_N_INVALIDOP_RESULTS = 12)
#endif

	integer*4 invres(0: FPE_N_INVALIDOP_RESULTS )

	common / invalidop_results / invres


C	There are ten cases in which an offending operand is replaced.  
C	The common block named 'invalidop_operands' is consulted for 
C	user-initialized codes for these cases.  Note that the final
C	four entries on only valid on mips3 and later processors.
C	The size of array 'invop' is actually smaller on the earlier
C	processors.  A declaration for this common block, which 
C	contains only the array invop, is below.  Each element 
C	governs the following cases:

C	---index---
C	#  mnemonic		exception condition
C	--------------------------------------------------------------
C	0  (none)		(ignored)
C	1   FPE_SQRT_NEG_X  	sqrt(-x) 
C	2   (unused)
C	3   FPE_CVTW_OVERFL 	conversion to int*4 caused target to overflow
C	4   FPE_CVTW_NAN 	conversion of NaN to int*4
C	5   FPE_CVTW_INF 	conversion of infinity to int*4
C	6   FPE_UNORDERED_CMP 	comparison to NaN
C	7   FPE_SNAN_OP 	operand was Signaling Nan
C	8   FPE_CVTL_OVERFL 	conversion to int*8 caused target to overflow
C	9   FPE_CVTL_NAN 	conversion of NaN to int*8
C	10  FPE_CVTL_INF 	conversion of infinity to int*8
C	11  FPE_RSQRT_NEG_X  	reciprocal sqrt(-x) 
	
C		if the corresponding code in the array is  FPE_APPROPRIATE ,
C		the element is uninitialized or is not a legal value, 
C		the instruction is re-issued with the same operands and
C		floating point traps disabled.
	
C  invalid ops for which the offending operand is replaced  

 	integer*4  FPE_SQRT_NEG_X      	 
	parameter ( FPE_SQRT_NEG_X      	= 1)

C  the following entry is obsolete and unused

 	integer*4  FPE_CVT_OVERFL      	 
	parameter ( FPE_CVT_OVERFL      	= 2)

C  the following 3 entries have been renamed (see below)

 	integer*4  FPE_TRUNK_OVERFL      	 
	parameter ( FPE_TRUNK_OVERFL      	= 3)
 	integer*4  FPE_CVT_NAN 		 
	parameter ( FPE_CVT_NAN 		= 4)
 	integer*4  FPE_CVT_INF 		 
	parameter ( FPE_CVT_INF 		= 5)

 	integer*4  FPE_CVTW_OVERFL      	 
	parameter ( FPE_CVTW_OVERFL      	= 3)
 	integer*4  FPE_CVTW_NAN 		 
	parameter ( FPE_CVTW_NAN 		= 4)
 	integer*4  FPE_CVTW_INF 		 
	parameter ( FPE_CVTW_INF 		= 5)

 	integer*4  FPE_UNORDERED_CMP 	 
	parameter ( FPE_UNORDERED_CMP 	        = 6)
 	integer*4  FPE_SNAN_OP 		 
	parameter ( FPE_SNAN_OP 		= 7)

#if (_MIPS_SIM == _ABIO32)

 	integer*4  FPE_N_INVALIDOP_OPERANDS   
	parameter ( FPE_N_INVALIDOP_OPERANDS    = 7)
#else

C  the following 4 entries are new for mips3/mips4

 	integer*4  FPE_CVTL_OVERFL      	 
	parameter ( FPE_CVTL_OVERFL      	= 8)
 	integer*4  FPE_CVTL_NAN 		 
	parameter ( FPE_CVTL_NAN 		= 9)
 	integer*4  FPE_CVTL_INF 		 
	parameter ( FPE_CVTL_INF 		= 10)
 	integer*4  FPE_RSQRT_NEG_X      	 
	parameter ( FPE_RSQRT_NEG_X      	= 11)


 	integer*4  FPE_N_INVALIDOP_OPERANDS   
	parameter ( FPE_N_INVALIDOP_OPERANDS    = 19)
#endif
	

	integer*4 invop(0: FPE_N_INVALIDOP_OPERANDS )
	common / invalidop_operands / invop

C	Once handle_sigfpes has been called, the values for the
C	various conditions are set.  Subsequent assignments to these
C	arrays will have no effect, unless handling is suspended
C	and resumed.


