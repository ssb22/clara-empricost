#ifndef WORK_H
#define WORK_H
class Work { /* base class added 2026 to help Elara */
public:
	Work() {}
	virtual ~Work() {}
	virtual void outputAndClear()=0;
};
#endif // WORK_H
