#include "Radix.hpp"

int Radix::MaxStepNumber()
{

    int max = 0;

    for (int i = 0; i < length; i++)
    {
        int step = StepCount(numbers[i]);
        if (step > max)
            max = step;
    }

    return max;
}

int Radix::StepCount(int number)
{
    number = abs(number);
    int step = 0;

    while (number > 0)
    {
        step++;
        number /= 10;
    }

    return step;
}

Radix::Radix(int *numbers, int length)
{
    this->numbers = new int[length];
    this->length = length;
    for (int i = 0; i < length; i++)
    {
        this->numbers[i] = numbers[i];
    }

    queues = new Queue *[10];
    for (int i = 0; i < 10; i++)
    {
        queues[i] = new Queue();
    }
    maxStep = MaxStepNumber();
}

int *Radix::Sort()// there is small problems with this radix 
{
    int numberIndex = 0;

    for (; numberIndex < length; numberIndex++)
    {
        int stepValue = numbers[numberIndex] % 10;
        int num = numbers[numberIndex];
        queues[stepValue]->enqueue(num);
    }

    for (int i = 1; i < maxStep; i++)
    {
        for (int index = 0; index < 10; index++)
        {
            int count = queues[index]->count();
            for (int len = 0; len < count; len++)
            {
                int number = queues[index]->peek();
                queues[index]->dequeue();
                int stepValue = (number / (int)pow(10, i)) % 10;
                queues[stepValue]->enqueue(number);
            }
        }
    }

    int *ordered = new int[length];
    numberIndex = 0;

    for (int index = 0; index < 10; index++)
    {
        while (!queues[index]->isEmpty())
        {
            int number = queues[index]->peek();
            ordered[numberIndex++] = number;
            queues[index]->dequeue();
        }
    }

    return ordered;
}

Radix::~Radix()
{
    delete[] numbers;

    for (int i = 0; i < 10; i++)
    {
        delete queues[i];
    }

    delete[] queues;
}