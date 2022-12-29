#ifndef emgrConst_h_
#define emgrConst_h_

enum EmgrEventClass {
   EmgrAdminEventClass = 0x01
};

enum EmgrAdminEventType {
   EmgrSubscribe = 0x01,
   EmgrUnsubscribe,
   EmgrQuery,
   EmgrReturn,
   EmgrRemoteSubscribe,
   EmgrRemoteUnsubscribe
};

enum EmgrConsumerType {
   EmgrDsoConsumer     = 0x1,
   EmgrExecConsumer    = 0x2,
   EmgrShmExecConsumer = 0x3,
   EmgrForwardConsumer = 0x4
};

extern const char* AdminIClassStr;
extern const char* AdminITypeStr;
extern const char* AdminISourceStr;
extern const char* AdminIOriginStr;
extern const char* AdminIAppnameStr;
extern const char* AdminIPriorityStr;
extern const char* AdminIFacilityStr;
extern const char* AdminIRegexpStr;
extern const char* AdminIMTypeStr;
extern const char* AdminIMClassStr;
extern const char* AdminITmFreqStr;
extern const char* AdminICntFreqStr;

extern const char* AdminCondFlagTag;

extern const char* SubscrConsumerStr;
extern const char* SubscrFrwdAuthProc;

extern const char* PriorityTagStr;
extern const char* FacilityTagStr;
extern const char* MessageTagStr;

extern const char* MessageTagStr;
extern const char* HostTagStr;
extern const char* TimeTagStr;
extern const char* CountTagStr;

extern const char* ForwardPathTagStr;

extern const char* ReturnHostTagStr;
extern const char* ReturnPortTagStr;
extern const char* ReturnPathTagStr;
extern const char* EventIdTagStr;

extern const char* EventsInRespTagStr;

extern const char* SubscrStatusTagStr;
extern const char* SubscrStatusMaskTagStr;

extern const char* IntegrityObjTagStr;

#endif
