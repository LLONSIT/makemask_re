! 
!  Copyright 1992-1997 Silicon Graphics,  Inc.
!  ALL RIGHTS RESERVED
!  
!  THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF SGI
!  The copyright notice above does not evidence any  actual  or
!  intended  publication of this source code and material is an
!  unpublished work by Silicon  Graphics,  Inc.  This  material
!  contains CONFIDENTIAL INFORMATION that is the property and a
!  trade secret of Silicon Graphics, Inc. Any use,  duplication
!  or  disclosure  not  specifically  authorized  in writing by
!  Silicon Graphics is  strictly  prohibited.  THE  RECEIPT  OR
!  POSSESSION  OF  THIS SOURCE CODE AND/OR INFORMATION DOES NOT
!  CONVEY ANY RIGHTS TO REPRODUCE, DISCLOSE OR  DISTRIBUTE  ITS
!  CONTENTS,  OR  TO MANUFACTURE, USE, OR SELL ANYTHING THAT IT
!  MAY DESCRIBE, IN WHOLE OR IN PART.
!  
!  U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND
!  Use, duplication or disclosure by the Government is  subject
!  to  restrictions  as  set  forth  in  FAR 52.227.19(c)(2) or
!  subparagraph (c)(1)(ii) of the Rights in Technical Data  and
!  Computer  Software  clause  at  DFARS 252.227-7013 and/or in
!  similar or successor clauses in the FAR, or the DOD or  NASA
!  FAR  Supplement.  Unpublished  --  rights reserved under the
!  Copyright Laws of the United States. Contractor/manufacturer
!  is Silicon Graphics, Inc., 2011 N. Shoreline Blvd., Mountain
!  View, CA 94039-7311
!
!
!	f90sigfpe.h - constants and data areas for the floating-point
!	exception-handling package when Fortran 90 is the native language. 
!
!	The MIPS floating-point accelerator may raise floating-point exceptions
!	due to five conditions:
!	FPE_OVERFL (overflow), FPE_UNDERFL (underflow), FPE_DIVZERO
!	(divide-by-zero), FPE_INEXACT (inexact result), or FPE_INVALID 
!	(invalid operand, e.g. infinity). 
!
!	Usually these conditions are masked and do not cause a floating-point
!	exception; instead, a default value is substituted for the result of
!	the operation and the program continues silently.  This event may be
!	intercepted by causing an exception to be raised.  Once an exception
!	is raised, the specific conditions which caused the exception may be 
!	determined, and more appropriate action taken.  This package provides a
!	mechanism for 'handling' such exceptions, classifying them by the 
!	conditions which caused them, and substituting a value, either a default
!	value or one supplied by the user.  This package also includes mechanisms
!	useful in debugging code that causes traps : stack trace, trap counts, 
!	abort and exit functions.  This package is provided for all of the above
!	conditions except FPE_INEXACT.  Two options exist to initiate trap 
!	handling:  the programmable interface, and the environment variable 
!	(runtime) interface.
!
!        *********************************************************************
!       The Runtime interface:
!
!       Link time switch -lfpe:
!	In order to acquire the trap handler runtime interface, link the program
!	with the switch -lfpe.   Traps will then be handled according to the
!       runtime environment variable TRAP_FPE.
!
!      TRAP_FPE:
!	This runtime environment variable specifies how the enabled trap handler
!	shall behave.  If TRAP_FPE is undefined, the program will execute with
!	sgi defaults (as found in the default values of sigfpe: 
!	array fsigfpe().repls; see below).  To execute user routine as if it 
!	were not compiled -lfpe, use TRAP_FPE=OFF
!
!      Syntax:
!
!	The string "TRAP_FPE" will be checked as an environment variable, in
!	upper case letters only.  The string defining the actions of the trap 
!	handler can be in either upper case, or lower case for the user's 
!	convenience.
!
!	The TRAP_FPE variable can take one of two forms:  either a "global"
!	value, or a list of individual items.  The two forms cannot be combined.
!	The global form is given by:
!
!	setenv TRAP_FPE global_value
!
!	where global_value takes on one of the following values:
!
!		"" or OFF
!					Execute the program with no trap handling 
!					enabled.  Same as linking WITHOUT -lfpe.
!					Same as TRAP_FPE undefined.
!		ON
!					Same as TRAP_FPE="ALL=DEFAULT".
!
!	Alternately, replacement values and actions may be specified for
!	each of the possible trap types individually. This is accomplished by:
!
!	setenv TRAP_FPE  "item;item;item...."
!
!					TRAP_FPE is set to a list of items. 
!					The length of this is limited by csh.
!
!		an item can be one of the following:

!			traptype=statuslist
!					where traptype defines the specific
!					floating point exception to enable,
!					and statuslist defines the list of
!					actions upon encountering the trap.
!			DEBUG
!					confirm the parsing of the environment
!					variable and the trap settings.
!
!
!		trap type can be one of the following literal strings:
!
!			UNDERFL		underflow
!
!			OVERFL		overflow
!
!			DIVZERO		divide by zero	
!
!			INVALID		invalid operand
!
!			ALL		all of the above
!
!		statuslist is a list separated by commas.  It contains an 
!		optional symbolic replacement value and an optional list of
!		actions.
!
!		replacement values:
!
!			DEFAULT		Use the predefined SGI default
!					(from sigfpe, fsigfpe().repls)
!					as the return result, and continue
!					execution.  If no other replacement
!					value is specified, this is the
!					default.
!			
!			APPROPRIATE	Use IEEE standard results as the return
!					result for FPE_OVERFL, FPE_DIVZERO, and
!					FPE_INVALID exceptions.  Use FPE_ZERO
!					for FPE_UNDERFL exceptions.
!
!			ZERO		substitute FPE_ZERO as the return result.
!
!			MIN		substitute FPE_MIN as the return result.
!
!			MAX		substitute FPE_MIN as the return result.
!
!			INF		substitute FPE_INF as the return result.
!
!			NAN		substitute FPE_NAN as the return result.
!
!			FLUSH_ZERO	set the flush to zero bit in the Control 
!					Status Register.  Causes flush to zero 
!					without invoking the trap handler.  Works
!					only for underflow on the R4000 and later
!					processors.  Works like ZERO for the R3000.
!				
!		actions:  COUNT(n)
!					A count of the trap type will be printed 
!					to stderr at the end of execution of the 
!					program, and every nth trap. 
!			
!		These actions take an optional integer in parentheses:
!
!			ABORT(n)	Core dump and abort program upon encountering
!					the nth trap, default is 1.
!
!			EXIT(n)		Exit program without coredump upon encountering
!					the nth trap, default is 1.
!
!			TRACE(n)	If trap is encountered, print a stack trace to 
!					stderr. Print this stack trace up to n times.
!					Default	is 10.
!
!       Example:
!
!		setenv TRAP_FPE "ALL=COUNT;UNDERFLOW=ZERO;OVERFLOW=APPROPRIATE,
!		TRACE(5),ABORT(100); DIVZERO=ABORT"
!
!	count all traps, print final results (even on abort) to stderr,
!	underflow to zero, overflow to IEEE, trace first five overflows, if
!	100 overflows occur then abort, abort on first zero divide.
!
!        *********************************************************************
!	The programmable interface:
!	Control is initiated (and canceled) by calling the function handle_sigfpes.
!	The function takes four arguments:
!
!		handle_sigfpes(onoff, en_mask, user_routine,
!			abort_action, abort_routine)
!
!		   onoff - a flag indicating whether handling is 
!			being turned on (onoff == FPE_ON) or 
!			debug (onoff = FPE_DEBUG)
!			off (onoff != FPE_ON && onoff != FPE_DEBUG)
!	
!		   The remaining parameters are only valid if onoff == FPE_ON
!		   or FPE_DEBUG.
!
!		   en_mask - indicates which of the four conditions should
!			raise a floating-point exception.  This parameter
!			is only valid if onoff == FPE_ON or FPE_DEBUG, and is
!			the sum of FPE_EN_UNDERFL, FPE_EN_OVERFL, FPE_EN_DIVZERO,
!			and FPE_EN_INVALID
!
!		   user_routine - The address of a user's routine which
!			is called to set the value.  This routine is called
!			if the replacement value code for the condition-at-hand
!			is FPE_USER_DETERMINED (see below). It
!			is invoked with the following parameters:
!
!			user_routine(exception, val)
!			integer *4 exception(0:4)
!			integer *4 val(2)
!
!			The exception array contains useful information
!			concerning the exception.  Its elements are
!			FPE_EXCEPTION_TYPE (0), FPE_INVALID_ACTION (1),
!			FPE_INVALID_TYPE (2), FPE_VALUE_TYPE (3), and
!			FPE_VALUE_SIGN (4):
!	
!			FPE_EXCEPTION_TYPE : FPE_OVERFL, FPE_UNDERFL, etc.

!			FPE_INVALID_ACTION : FPE_SET_RESULT if result is being
!				set; FPE_REPL_OPERAND if operand is being
!				replaced.

!			FPE_INVALID_TYPE: if exception_type is FPE_INVALID, this
!				indicates the type of FPE_INVALID
!				exception which occurred: 
!				FPE_CVTW_OVERFL, FPE_ZERO_TIMES_INF, etc.

!			FPE_VALUE_TYPE: FPE_SINGLE, FPE_DOUBLE, or FPE_WORD

!			FPE_VALUE_SIGN: The suggested sign for the value, 
!				based on an analysis of the instruction:
!				FPE_NEGATIVE or FPE_POSITIVE

!			val: an array in which the modified value should
!				be placed.  If an operand is being replaced,
!				val has a copy of the current operand.
!	
!		   abort_action - If the handler encounters an unexpected 
!			condition, an inconsistency, or begins looping, 
!			this flag indicates what action should be taken.  The 
!			possible values are:
!	
!				FPE_TURN_OFF_HANDLER_ON_ERROR - instruct the 
!					floating-point-accelerator to cease
!					causing exceptions and continue.
!					(i.e., disable handling)
!
!				FPE_ABORT_ON_ERROR - kill the process after 
!					giving an error message and possibly 
!					calling a user-supplied cleanup routine.
!
!				FPE_REPLACE_HANDLER_ON_ERROR - install the 
!					indicated user routine as the handler
!					when such an error is encountered.
!					Future floating-point exceptions will
!					branch to the user-routine. 
!					(see signal(2))
!
!				FPE_USER_HANDLER - install the indicated user 
!					routine as the handler.  (see signal(2))
!	
!		    abort_routine - When a fatal error (i.e., one described
!			under 'abort_action' above) is encountered, this
!			argument is used as the address of a user routine.  
!			If abort_action is FPE_ABORT_ON_ERROR, and this argument
!			is non-zero, it is used as the address of a routine
!			to call before aborting.  The routine is invoked
!			with a single argument - the pc of the exception.
!
!			If abort_action is FPE_REPLACE_HANDLER_ON_ERROR, or
!			FPE_USER_HANDLER, and abort_routine is non-zero, it 
!			will be installed as the floating point exception
!			handler.  In the former case, the instruction which
!			caused the unexpected exception will be re-executed, 
!			causing a new exception, and abort_routine entered.
!			(see signal(2)).
!
!			If abort_action is _ABORT_ON_ERROR, then abort_routine
!			is invoked with the following parameter:
!
!			abort_routine( pc )
!			integer *4 pc
!
!			For mips3 and later processors, program counters are
!			8 bytes in length, and then abort_routine should be
!			invoked with the following parameter:
!
!			abort_routine( pc )
!			integer *8 pc
!
!			pc is the program counter of the instruction
!			which caused the exception (pc + 4, if the
!			instruction is in a branch delay slot).
!
!			If abort_action is _REPLACE_HANDLER_ON_ERROR or
!			FPE_USER_HANDLER (i.e. abort_routine is actually a
!			floating point exception handler), then abort_routine
!			is invoked with the following parameters:
!
!			int abort_routine( sig, code, sc )
!			int sig, code;
!			struct sigcontext *sc;
!
!			See signal(5) and /usr/include/sigfpe.h for more
!			information on user-defined floating point exception
!			handlers.
!

	



 	integer(4)  FPE_OFF   
	parameter ( FPE_OFF = 0)
 	integer(4)  FPE_ON   
	parameter ( FPE_ON = 1)
 	integer(4)  FPE_DEBUG
	parameter ( FPE_DEBUG = 2)
	
 	integer(4)  FPE_ABORT_ON_ERROR   
	parameter ( FPE_ABORT_ON_ERROR = 0)
 	integer(4)  FPE_TURN_OFF_HANDLER_ON_ERROR   
	parameter ( FPE_TURN_OFF_HANDLER_ON_ERROR = 1)
 	integer(4)  FPE_REPLACE_HANDLER_ON_ERROR   
	parameter ( FPE_REPLACE_HANDLER_ON_ERROR = 2)
 	integer(4)  FPE_USER_HANDLER   
	parameter ( FPE_USER_HANDLER = 3)
	
!  	exceptions 	

 	integer(4)  FPE_UNDERFL   
	parameter ( FPE_UNDERFL = 1)
 	integer(4)  FPE_OVERFL    
	parameter ( FPE_OVERFL = 2)
 	integer(4)  FPE_DIVZERO   
	parameter ( FPE_DIVZERO = 3)
 	integer(4)  FPE_INVALID   
	parameter ( FPE_INVALID = 4)
 	integer(4)  FPE_INT_OVERFL   
	parameter ( FPE_INT_OVERFL = 5)
 	integer(4)  FPE_N_EXCEPTION_TYPES   
	parameter ( FPE_N_EXCEPTION_TYPES = 5)
	
 	integer(4)  FPE_EN_UNDERFL   
	parameter ( FPE_EN_UNDERFL = 2)
 	integer(4)  FPE_EN_OVERFL    
	parameter ( FPE_EN_OVERFL = 4)
 	integer(4)  FPE_EN_DIVZERO   
	parameter ( FPE_EN_DIVZERO = 8)
 	integer(4)  FPE_EN_INVALID   
	parameter ( FPE_EN_INVALID = 16)
 	integer(4)  FPE_EN_INT_OVERFL   
	parameter ( FPE_EN_INT_OVERFL = 32)

!  types 

 	integer(4)  FPE_SINGLE   
	parameter ( FPE_SINGLE = 0)
 	integer(4)  FPE_DOUBLE   
	parameter ( FPE_DOUBLE = 1)
 	integer(4)  FPE_WORD      
	parameter ( FPE_WORD = 2)
 	integer(4)  FPE_LONGWORD      
	parameter ( FPE_LONGWORD = 3)
 	integer(4)  FPE_FIRST_TYPE   
	parameter ( FPE_FIRST_TYPE = FPE_SINGLE )
 	integer(4)  FPE_LAST_TYPE   
	parameter ( FPE_LAST_TYPE = FPE_LONGWORD )

	
!  signs 

 	integer(4)  FPE_POSITIVE   
	parameter ( FPE_POSITIVE = 0)
 	integer(4)  FPE_NEGATIVE   
	parameter ( FPE_NEGATIVE = 1)

	
!  actions  

 	integer(4)  FPE_SET_RESULT   
	parameter ( FPE_SET_RESULT = 0)
 	integer(4)  FPE_REPL_OPERAND   
	parameter ( FPE_REPL_OPERAND = 1)
 	integer(4)  FPE_REPL_RS   
	parameter ( FPE_REPL_RS = 1)
 	integer(4)  FPE_REPL_RT   
	parameter ( FPE_REPL_RT = 2)

	
!  elements of exception array 

 	integer(4)  FPE_EXCEPTION_TYPE   
	parameter ( FPE_EXCEPTION_TYPE = 0)
 	integer(4)  FPE_INVALID_ACTION   
	parameter ( FPE_INVALID_ACTION = 1)
 	integer(4)  FPE_INVALID_TYPE     
	parameter ( FPE_INVALID_TYPE = 2)
 	integer(4)  FPE_VALUE_TYPE       
	parameter ( FPE_VALUE_TYPE = 3)
 	integer(4)  FPE_VALUE_SIGN       
	parameter ( FPE_VALUE_SIGN = 4)

	

!	When an exception is encountered, the handler examines the instruction
!	causing the exception and the state of the floating-point accelerator
!	to determine the correct action to take, and the program is continued.
!	In most cases of floating-point exceptions, e.g.  FPE_UNDERFL, FPE_OVERFL, 
!	FPE_DIVZERO, and some instances of FPE_INVALID, an appropriate value is 
!	substituted for the result of the operation, and the instruction 
!	which caused the exception is skipped.  For most exceptions arising 
!	due to an invalid operand (FPE_INVALID exceptions), more meaningful 
!	behavior may be obtained by replacing an erroneous operand.  In this
!	case, the operand is replaced, and the instruction re-issued.
!	
!	For exceptions which always warrant the setting of the result, the
!	value used is determined by the exception type (FPE_UNDERFL, FPE_OVERFL,
!	or FPE_DIVZERO).
!
!	These default values may be overridden by initializing a common block 
!	named 'sigfpe'.  A declaration for this common block is below.  
!	It has a single member, the array 'fsigfpe'.  
!	Each element in fsigfpe().repls is interpreted as an integer code used to 
!	select one of a set of replacement values, or the code FPE_USER_DETERMINED,
!	which indicates that the user's routine should be invoked to provide the 
!	replacement value.  If the code is not FPE_USER_DETERMINED, the appropriately-
!	typed (single- or double- precision) and appropriately-signed replacement 
!	value is then substituted in the operation causing the exception.  The
!	integer codes, and the corresponding replacement values they select, are 
!	listed below:
!
!		FPE_ZERO  - use zero as the replacement value.
!
!		FPE_MIN   - use the appropriately-typed minimum value as 
!			    the replacement. (i.e., the smallest number
!			    which is representable in that format)
!
!		FPE_MAX   - use the appropriately-typed maximum value as 
!			    the replacement.
!
!		FPE_INF   - use the appropriately-typed value for infinity 
!			    as the replacement.
!
!		FPE _NAN  - use the appropriately-typed value for not-a-number 
!			    as the replacement.
!
!		FPE_APPROPRIATE - use a handler-supplied appropriate value 
!			    as the replacement.  These are _ZERO for _UNDERFL,
!			    and values which will produce the IEEE result the
!			    instruction would have produced if it had not been
!			    trapped.
!
!		FPE_USER_DETERMINED - call the user's routine to set the value.
!
!		FPE_NEG   - use the negative of the original argument (valid
!			    only for cases FPE_SQRT_NEG_X and FPE_RSQRT_NEG_X
!			    (see below)
!
!		FPE_FLUSH_ZERO 	- set the flush to zero bit in the Control Status
!			    Register.  Causes flush to zero without invoking
!			    the trap handler.  Works only for underflow traps
!			    on the R4000 and later processors.  Works like 
!			    FPE_ZERO for the R3000.
!				
!
!	
!	If the replacement-value code for FPE_INVALID exceptions is FPE_USER_DETERMINED,
!	the replacement value for all FPE_INVALID exceptions will be obtained from 
!	the user_routine.  Otherwise, the code for FPE_INVALID is ignored, as this 
!	exception has cases which warrant the replacement of an operand as well
!	as cases which warrant the setting of the result (see below).
!	
!	
!	The elements of this array of structures are interpreted as follows:
!
!		fsigfpe(0) is ignored.
!		fsigfpe(1) is the structure for  FPE_UNDERFL 
!		fsigfpe(2) is the structure for  FPE_OVERFL 
!		fsigfpe(3) is the structure for  FPE_DIVZERO 
!		fsigfpe(4) is the structure for  FPE_INVALID  
!
!	Each structure contains the following:
!
!		structure /sigfpe_template/
!		      integer(4) repls			The replacement code
!		      integer(4) count			The count limit
!		      integer(4) trace			The trace limit
!		      integer(4) abort			The abort limit
!		      integer(4) exit 			The exit limit
!		end structure
!
!	Each limit defines the number of traps that will be executed before the 
!	defined action occurs:
!
!	count : print a count of all the traps that have count enabled.
!	trace : print a dbx stack trace. 
!	abort : abort with a core dump.
!	exit  : exit program, no core dump.
!
!
!	If no sigfpe common block is initialized, no count, trace, exit or 
!	abort actions will be performed.  The default values are used as if 
!	the following initialization had been performed:
!
!	data fsigfpe.repls / 0,  FPE_ZERO,  FPE_APPROPRIATE,  FPE_APPROPRIATE,  0  /
!
!	Thus, the default replacement code for FPE_UNDERFL is FPE_ZERO, for 
!	FPE_OVERFL is FPE_APPROPRIATE, etc.  Default replacement codes for 
!	FPE_INVALID are determined from common blocks invalidop_results and
!	invalidop_operands (see below).
!
!
!  the possible replacement values:  FPE_ZERO = 0, FPE_MIN = minimum valid number, etc. 


 	integer(4)  FPE_ZERO   
	parameter ( FPE_ZERO = 1)
 	integer(4)  FPE_MIN   
	parameter ( FPE_MIN = 2)
 	integer(4)  FPE_MAX   
	parameter ( FPE_MAX = 3)
 	integer(4)  FPE_INF   
	parameter ( FPE_INF = 4)
 	integer(4)  FPE_NAN   
	parameter ( FPE_NAN = 5)
 	integer(4)  FPE_FLUSH_ZERO
	parameter ( FPE_FLUSH_ZERO = 6)
 	integer(4)  FPE_APPROPRIATE   
	parameter ( FPE_APPROPRIATE = 7)
 	integer(4)  FPE_USER_DETERMINED   
	parameter ( FPE_USER_DETERMINED = 8)
 	integer(4)  FPE_NEG   
	parameter ( FPE_NEG = 9)
 	integer(4)  FPE_MIN_REPL   
	parameter ( FPE_MIN_REPL = FPE_ZERO )
 	integer(4)  FPE_MAX_REPL   
	parameter ( FPE_MAX_REPL = FPE_NEG )


	type sigfpe_template
           sequence
           integer(4) repls
           integer(4) count
           integer(4) trace
           integer(4) abort
           integer(4) exit 
	end type sigfpe_template

	type (sigfpe_template) fsigfpe (0: FPE_N_EXCEPTION_TYPES )

	common /sigfpe / fsigfpe

!	For  FPE_INVALID  exceptions, the correct action may be either to
!	set the result and skip the instruction, or to replace an
!	operand and retry the instruction.  

!	There are four cases in which the result is set.  The common 
!	block named 'invalidop_results' is consulted for user-initialized
!	codes for these cases.  A declaration for this common block,
!	which contains only the array 'invres', is below.  Each element 
!	governs the following cases:
	
!	---index---
!	#  mnemonic			exception condition
!	--------------------------------------------------------------
!	0  (none)			(ignored)
!	1   FPE_MAGNITUDE_INF_SUBTRACTION subtraction of infinities: 
!	2   FPE_ZERO_TIMES_INF 	        multiplication 0 * infinity
!	3   FPE_ZERO_DIV_ZERO 	        0/0
!	4   FPE_INF_DIV_INF 		infinity / infinity

!		if the corresponding code in the array is  FPE_APPROPRIATE ,
!		uninitialized, or not a legal value, the result used is
	
!		for  FPE_MAGNITUDE_INF_SUBTRACTION  -  FPE_NAN
!		for  FPE_ZERO_TIMES_INF 	    -  FPE_NAN
!		for  FPE_ZERO_DIV_ZERO 		    -  FPE_NAN
!		for  FPE_INF_DIV_INF 		    -  FPE_NAN
	
!  invalid ops for which the result is set  

 	integer(4)  FPE_MAGNITUDE_INF_SUBTRACTION   
	parameter ( FPE_MAGNITUDE_INF_SUBTRACTION = 1)
 	integer(4)  FPE_ZERO_TIMES_INF  	 
	parameter ( FPE_ZERO_TIMES_INF = 2)
 	integer(4)  FPE_ZERO_DIV_ZERO   	 
	parameter ( FPE_ZERO_DIV_ZERO = 3)
 	integer(4)  FPE_INF_DIV_INF     	 
	parameter ( FPE_INF_DIV_INF = 4)

 	integer(4)  FPE_N_INVALIDOP_RESULTS   
	parameter ( FPE_N_INVALIDOP_RESULTS = 12)

	integer(4) invres(0: FPE_N_INVALIDOP_RESULTS )

	common / invalidop_results / invres


!	There are ten cases in which an offending operand is replaced.  
!	The common block named 'invalidop_operands' is consulted for 
!	user-initialized codes for these cases.  Note that the final
!	four entries on only valid on mips3 and later processors.
!	The size of array 'invop' is actually smaller on the earlier
!	processors.  A declaration for this common block, which 
!	contains only the array invop, is below.  Each element 
!	governs the following cases:

!	---index---
!	#  mnemonic		exception condition
!	--------------------------------------------------------------
!	0  (none)		(ignored)
!	1   FPE_SQRT_NEG_X  	sqrt(-x) 
!	2   (unused)
!	3   FPE_CVTW_OVERFL 	conversion to int(4) caused target to overflow
!	4   FPE_CVTW_NAN 	conversion of NaN to int(4)
!	5   FPE_CVTW_INF 	conversion of infinity to int(4)
!	6   FPE_UNORDERED_CMP 	comparison to NaN
!	7   FPE_SNAN_OP 	operand was Signaling Nan
!	8   FPE_CVTL_OVERFL 	conversion to int*8 caused target to overflow
!	9   FPE_CVTL_NAN 	conversion of NaN to int*8
!	10  FPE_CVTL_INF 	conversion of infinity to int*8
!	11  FPE_RSQRT_NEG_X  	reciprocal sqrt(-x) 
	
!		if the corresponding code in the array is  FPE_APPROPRIATE ,
!		the element is uninitialized or is not a legal value, 
!		the instruction is re-issued with the same operands and
!		floating point traps disabled.
	
!  invalid ops for which the offending operand is replaced  

 	integer(4)  FPE_SQRT_NEG_X      	 
	parameter ( FPE_SQRT_NEG_X      	= 1)

!  the following entry is obsolete and unused

 	integer(4)  FPE_CVT_OVERFL      	 
	parameter ( FPE_CVT_OVERFL      	= 2)

!  the following 3 entries have been renamed (see below)

 	integer(4)  FPE_TRUNK_OVERFL      	 
	parameter ( FPE_TRUNK_OVERFL      	= 3)
 	integer(4)  FPE_CVT_NAN 		 
	parameter ( FPE_CVT_NAN 		= 4)
 	integer(4)  FPE_CVT_INF 		 
	parameter ( FPE_CVT_INF 		= 5)

 	integer(4)  FPE_CVTW_OVERFL      	 
	parameter ( FPE_CVTW_OVERFL      	= 3)
 	integer(4)  FPE_CVTW_NAN 		 
	parameter ( FPE_CVTW_NAN 		= 4)
 	integer(4)  FPE_CVTW_INF 		 
	parameter ( FPE_CVTW_INF 		= 5)

 	integer(4)  FPE_UNORDERED_CMP 	 
	parameter ( FPE_UNORDERED_CMP 	        = 6)
 	integer(4)  FPE_SNAN_OP 		 
	parameter ( FPE_SNAN_OP 		= 7)

 	integer(4)  FPE_CVTL_OVERFL      	 
	parameter ( FPE_CVTL_OVERFL      	= 8)
 	integer(4)  FPE_CVTL_NAN 		 
	parameter ( FPE_CVTL_NAN 		= 9)
 	integer(4)  FPE_CVTL_INF 		 
	parameter ( FPE_CVTL_INF 		= 10)
 	integer(4)  FPE_RSQRT_NEG_X      	 
	parameter ( FPE_RSQRT_NEG_X      	= 11)


 	integer(4)  FPE_N_INVALIDOP_OPERANDS   
	parameter ( FPE_N_INVALIDOP_OPERANDS    = 19)
	

	integer(4) invop(0: FPE_N_INVALIDOP_OPERANDS )
	common / invalidop_operands / invop

!	Once handle_sigfpes has been called, the values for the
!	various conditions are set.  Subsequent assignments to these
!	arrays will have no effect, unless handling is suspended
!	and resumed.


