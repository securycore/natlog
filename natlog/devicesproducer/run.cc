#include "devicesproducer.ih"

void DevicesProducer::run()
try
{
                                        // see pcapfilter/callback for
                                        // handling incoming packets
    PcapFilter  in{ d_options[0], Record::IN, d_stdMsg, d_storage };
    PcapFilter out{ d_options[1], Record::OUT, d_stdMsg, d_storage };

    Signal::instance().add(SIGTERM, in);
    Signal::instance().add(SIGTERM, out);

    d_stdMsg << "starting: capturing " << d_options[0] << 
                              " and " << d_options[1] << endl;

    thread inThread(in);

    out();    

    inThread.join();

    if (out.stopped())
    {
        d_storage.setEmpty();
        throw Options::TERM_SIGNAL;
    }
}
catch (exception const &ex)
{
    d_storage.setEmpty();
    throw;
}





