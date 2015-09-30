class BoundedQLock {
	bool addremdbg = false;
	std::mutex enqLock;
	std::mutex deqLock;
	int ID;
	public:
		int capacity;
		std::atomic_int head;
		std::atomic_int tail;
		std::atomic_int size;
		std::unique_ptr<int[]> arr;
	void sayHello(){
		printf("no\n");
	}
	bool add(int val){
		enqLock.lock();
		if((size+1) > capacity){
			if(addremdbg) printf("af %d\n", val);
			enqLock.unlock();
			return false;
		}
		if(addremdbg) printf("ap %d\n", val);
		arr[tail] = val;
		tail = (tail.load()+1)%capacity;
		size++;
		enqLock.unlock();
		return true;
	}
	
	bool remove(int* result){
		deqLock.lock();
		if((size-1)<0){
			deqLock.lock();
			return false;
		}
		*result = arr[head];
		head = (head+1)%capacity;
		size--;
		deqLock.lock();
		return true;
	}
	
	BoundedQ(int capacity, int numElem){
		this->capacity = capacity;
		head = tail = 0;
		size = 0;
		arr.reset(new int[capacity]);
	}
	void print(){
		if(size==0)
			printf("<empty>\n");
		for(int i = 0; i < size;i++)
			printf("%d ", arr[(head.load() + i)%capacity]);
		printf("\n");
	}
};