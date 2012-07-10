#ifndef MEH_FILECONFIG_H
#define MEH_FILECONFIG_H

#include <allegro5/allegro.h>
#include <string>
#include <map>

using namespace std;

namespace meh {

class FileConfig {
    private:
        ALLEGRO_CONFIG* aConfig;
        string file;
        map<string, map<string, string> > mapValues;

        void read();

    protected:
    public:
        FileConfig(string filePath);
        ~FileConfig();

        map<string, map<string, string> >& values() { 
            return mapValues;
        }

        const char* getValue(const char* section, const char* entry) {
            return al_get_config_value(aConfig,section,entry);
        }
};

}

#endif 
