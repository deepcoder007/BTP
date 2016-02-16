
#include"config_node.h"

config_node::config_node(int ky)
{
    key=ky;
    v=-1;
    k=0;
    n=-1;
}

int config_node::getRobotPos()
{
    return v;
}

void config_node::setRobotPos(int pos)
{
    v=pos;
}

void setTotalNodes(int cnt)
{
    n

