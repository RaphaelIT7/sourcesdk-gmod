#ifndef IGMODDATATABLE_H
#define IGMODDATATABLE_H
#ifdef _WIN32
#pragma once
#endif
class CGMODVariant;
class IGMODDataTable
{
public:
	//virtual CGMODDataTable() = 0;
	virtual void GetKey(int) = 0;
	virtual void GetValue(int key) = 0;
	virtual void IncrementIterator(int&) = 0;
	virtual void Get(int) = 0;
	virtual void Set(int, CGMODVariant const &) = 0;
	virtual void Skip(bf_read*) = 0;
	virtual void HasKey(int) = 0;
	virtual void GetLocal(char const*) = 0;
	virtual void SetLocal(char const*, CGMODVariant const &) = 0;
	virtual void WriteProps(bf_read*, bf_write*, int);
	virtual void Compare(bf_read *, bf_read *, CGMODDataTable*, int) = 0;
	virtual void CopyFrom(void*, const void*, CGMODDataTable*) = 0;
	virtual void ClearLocal(char const*) = 0;
	virtual void Clear() = 0;
	virtual bool IsEmpty() = 0;
	virtual void Begin() = 0;
	virtual void Encode(void *,bf_write *) = 0;
	virtual void Decode(void*, bf_read*) = 0;
	virtual void End() = 0;

	// CGMODDataTable::Entry::~Entry()  
private:
	CThreadLocalBase s_CurrentTable;
	CThreadLocalBase s_TargetTick;
	CthreadLocalBase s_ReferenceTick;
};

#endif