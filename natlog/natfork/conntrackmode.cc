#include "natfork.ih"

void NatFork::conntrackMode()
{
    Options &options = Options::instance();

    char const *conntrack = options.conntrackPath().c_str();

    if (access(conntrack, R_OK | X_OK) != 0)
    {
        d_out << "[Fatal] Can't execute " << conntrack << endl;
        throw 1;
    }
    d_mode = CONNTRACK;
}
