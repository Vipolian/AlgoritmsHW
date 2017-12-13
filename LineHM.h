class LineHashingMap : public HashMap {
protected:
	vector<pair<int, int>*>* data;
	//
	int getNextPrime();
	virtual void resize(int capacity);
public:
	LineHashingMap();
	virtual ~LineHashingMap();
	virtual void insert(int key, int value);
	virtual pair<int, bool> find(int key);
	virtual void erase(int key);
	virtual void print(ostream& stream);
	virtual int getHash(int key);
	virtual pair<int, bool> min();
	virtual pair<int, bool> max();
	virtual void clear();
};

LineHashingMap::LineHashingMap() {
	data = new vector<pair<int, int>*>(PRIMARY_VECTOR_CAPACITY);
}

LineHashingMap::~LineHashingMap() {
	for (unsigned int i = 0; i < data->capacity(); ++i)
		delete data->at(i);
	delete data;
}

void LineHashingMap::clear() {
	for (unsigned int i = 0; i < data->capacity(); ++i)
		delete data->at(i);
	coefficient = 0.0f;
	data->clear();
	data->shrink_to_fit();
	data->resize(PRIMARY_VECTOR_CAPACITY);
}

void LineHashingMap::insert(int key, int value) {
	if (key > 0) {
		if (coefficient >= RESIZE_COEFF_VALUE)
			resize(getNextPrime());
		//
		int i;
		for (i = getHash(key); data->at(i) != nullptr && data->at(i)->first != INVALID_KEY; i = (i + INTERVAL) % data->capacity()) {
			if (data->at(i)->first == key) {
				data->at(i)->second = value;
				return;
			}
		}
		delete data->at(i);
		data->at(i) = new pair<int, int>(key, value);
		coefficient += 1.0f / (float)data->capacity();
	}
}

pair<int, bool> LineHashingMap::find(int key) {
	if (key > 0) {
		for (int i = getHash(key); data->at(i) != nullptr; i = (i + INTERVAL) % data->capacity()) {
			if (data->at(i)->first == key)
				return pair<int, bool>(data->at(i)->second, true);
		}
	}
	return pair<int, bool>(0, false);
}

void LineHashingMap::erase(int key) {
	if (key > 0) {
		for (int i = getHash(key); data->at(i) != nullptr; i = (i + INTERVAL) % data->capacity()) {
			if (data->at(i)->first == key) {
				data->at(i)->first = INVALID_KEY;
				coefficient -= 1.0f / (float)data->capacity();
				break;
			}
		}
	}
}

void LineHashingMap::print(ostream& stream) {
	stream << "PRINT\n";
	for (unsigned int i = 0; i < data->capacity(); ++i) {
		if (data->at(i) != nullptr && data->at(i)->first != INVALID_KEY)
			stream << "KEY: " << data->at(i)->first << "\tVALUE: " << data->at(i)->second << "\n";
	}
	stream << "\n\n";
}

int LineHashingMap::getHash(int key) {
	return key % data->capacity();
}

int LineHashingMap::getNextPrime() {
	bool flag = true;
	for (unsigned int i = data->capacity() * 2;; ++i, flag = true) {
		for (unsigned int j = 2; j < i - 1; ++j)
			if (i % j == 0) {
				flag = false;
				break;
			}
		if (flag) return i;
	}
}

pair<int, bool> LineHashingMap::min() {
	pair<int, bool> min(0, false);
	for (unsigned int i = 0; i < data->capacity(); ++i)
		if (data->at(i) != nullptr && data->at(i)->first != INVALID_KEY) {
			min.first = data->at(i)->second;
			min.second = true;
			break;
		}
	//
	for (unsigned int i = 0; i < data->capacity(); ++i)
		if (data->at(i) != nullptr && data->at(i)->first != INVALID_KEY)
			if (data->at(i)->second < min.first)
				min.first = data->at(i)->second;
	return min;
}

pair<int, bool> LineHashingMap::max() {
	pair<int, bool> max(0, false);
	for (unsigned int i = 0; i < data->capacity(); ++i)
		if (data->at(i) != nullptr && data->at(i)->first != INVALID_KEY) {
			max.first = data->at(i)->second;
			max.second = true;
			break;
		}
	//
	for (unsigned int i = 0; i < data->capacity(); ++i)
		if (data->at(i) != nullptr && data->at(i)->first != INVALID_KEY)
			if (data->at(i)->second > max.first)
				max.first = data->at(i)->second;
	return max;
}

void LineHashingMap::resize(int capacity) {
	vector<pair<int, int>*>* oldData = new vector<pair<int, int>*>(*data);
	coefficient = 0.0f;
	data->clear();
	data->resize(capacity);
	for (unsigned int i = 0; i < oldData->capacity(); ++i) {
		if (oldData->at(i) != nullptr && oldData->at(i)->first != INVALID_KEY)
			insert(oldData->at(i)->first, oldData->at(i)->second);
		delete oldData->at(i);
	}
	delete oldData;
}
