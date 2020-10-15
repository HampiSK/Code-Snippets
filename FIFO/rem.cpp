#include <queue>
#include <deque>
#include <iostream>
#include <map>
#include <iterator>
#include <functional>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <memory>
template <typename T, const int lenght, typename Container=std::deque<T>>
struct FIFO : std::queue<T, Container> 
{
	void update(const T & value) 
	{
		if (duplicate(value))
			return;
		else if	(this->size() < lenght || this->size()+1 == lenght)
			std::queue<T, Container>::push(value);
		else if (this->size() == lenght) 
		{
			std::queue<T, Container>::pop();
			std::queue<T, Container>::push(value);
		}
	}
	std::vector<T> get()
	{
		std::vector<T> frames;
		for (int i = 0; i < this->c.size(); i++)
			frames.push_back(this->c[i]);
		return frames;
	}
	private:
		bool duplicate(const T & find)
		{
			for (int i = 0; i < this->c.size(); i++)
			{
				if (this->c[i] == find)
					return true;
			}	
			return false;
		}	
};
// class FIFO
// {
// 	private:
// 	    int lenght;
// 		bool page_fault;
// 		std::deque<int> f_queue;

// 		bool duplicate(const int & find)
// 		{
// 			for (int i = 0; i < f_queue.size(); i++)
// 			{
// 				if (f_queue[i] == find)
// 					return true;
// 			}	
// 			return false;
// 		}	

// 	public:	
// 		FIFO(const int & set_lenght)	
// 		{
// 			lenght = set_lenght;
// 		}
// 		void update(const int & value) 
// 		{
// 			page_fault = true;
// 			if (duplicate(value))
// 				page_fault = false;
// 			else if	(f_queue.size() < lenght || f_queue.size()+1 == lenght)
// 				f_queue.push_back(value);
// 			else if (f_queue.size() == lenght) 
// 			{
// 				f_queue.pop_front();
// 				f_queue.push_back(value);
// 			}
// 		}
// 		std::vector<int> get()
// 		{
// 			std::vector<int> frames = {page_fault};
// 			for (int i = 0; i < f_queue.size(); i++)
// 				frames.push_back(f_queue[i]);
// 			return frames;
// 		}
// };

int main()
{	
	int input = 3;
	// std::cout<<"Size: ";
	// std::cin>> input; 
	const int s = input;
	FIFO<int, 3> q;
    //FIFO q(s);
	q.update(1);
	q.update(1);
	q.update(2);
	q.update(3);
	q.update(4);
	q.update(5);
	q.update(4);
}