#include <queue>
#include <deque>
#include <iterator>
#include <iostream>
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

int main()
{	
	FIFO<int, 3> f;
}
