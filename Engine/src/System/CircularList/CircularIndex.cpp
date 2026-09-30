#include "CircularIndex.h"

CircularIndex::CircularIndex(unsigned int bufferSize)
{
	this->size = bufferSize;
	assert(bufferSize > 1);
	this->mask = (bufferSize - 1);
	this->index = 0;
}

unsigned int CircularIndex::operator++(int)
{
	this->index++;
	this->index = this->index & this->mask;
	return this->index;
}
bool CircularIndex::operator==(const CircularIndex& tmp)
{
	assert(this->size == tmp.size);
	return(this->index == tmp.index);
}
bool CircularIndex::operator!=(const CircularIndex& tmp)
{
	assert(this->size == tmp.size);
	return(this->index != tmp.index);
}
unsigned int CircularIndex::getIndex() const
{
	return this->index;
}