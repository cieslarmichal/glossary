#include "Glossary.h"
#include "glog/logging.h"

int main(int argc, char* argv[])
{
    google::InitGoogleLogging(argv[0]);

    Glossary app;
    app.run();

    return 0;
}
