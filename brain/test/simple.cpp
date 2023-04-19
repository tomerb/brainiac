#include "../src/brain.h"

#include<unistd.h>

int main()
{
    brainiac::Brain::Instance().Start("../../cli/sample_config.yaml");
    sleep(10000);
    return 0;
}
