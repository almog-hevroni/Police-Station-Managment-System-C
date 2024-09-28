#ifndef EVIDENCE
#define EVIDENCE

typedef enum { eEyeWitness, eFingerPrint, eSuspiciousObject, eNoOfEvidence } evidenceType;
static const char* evidence[eNoOfEvidence] = { "Eye Witness", "Finger Print", "Suspicious Object" };

typedef struct {
    evidenceType evidenceType;
    char* description;
}Evidence;

void initEvidence(Evidence* theEvidence);
evidenceType getEvidenceType();
void printEvidence(const Evidence* theEvidence);
char* getEvidenceDescription();

#endif