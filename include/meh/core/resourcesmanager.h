#ifndef MEH_RESOURCES_MANAGER_H
#define MEH_RESOURCES_MANAGER_H

#include <map>
#include <string>

#include "ui/bitmap.h"
#include "core/sample.h"
#include "core/font.h"

using namespace std;

namespace meh {

class ResourcesManager {
    private:
        map<string, Bitmap*> mapBitmaps;
        map<string, Sample*> mapSamples;
        map<string, Font*> mapFonts;

    protected:
    public:
        /**
         * Default constructor.
         */
        ResourcesManager();
        /**
         * Destructor
         */
        ~ResourcesManager();

        /**
         * Returns a reference to the map of bitmaps.
         *
         * \return a reference to the map of bitmaps.
         */
        map<string, Bitmap*>& bitmaps() {
            return mapBitmaps;
        }

        /**
         * Returns a reference to the map of samples.
         *
         * \return a reference to the map of samples.
         */
        map<string, Sample*>& samples() {
            return mapSamples;
        }

        /**
         * Loads a Bitmap from a file and adds it to the ResourcesManager.
         *
         * <b>WARNING</b>
         *  - if the uniqueId is already used, the old Bitmap will be deleted
         *
         * @param uniqueId the unique name given to this Bitmap
         * @param filepath the path to the bitmap
         * @param videoMemory whether this Bitmap must be a video bitmap.
         *
         * \return a pointer to the Bitmap added to the ResourcesManager
         */
        Bitmap* loadBitmap(string uniqueId, string filepath, bool videoMemory = true);

        /**
         * Adds an existing Bitmap into the ResourcesManager
         *
         * <b>WARNING</b>
         *  - the memory of the bitmap will be managed by the ResourcesManager
         *  - if the uniqueId is already used, the old Bitmap will be deleted
         *
         * @param uniqueId the unique id of this resource
         * @param bitmap the Bitmap to delegate to the ResourcesManager
         *
         * \return a pointer to the Bitmap added to the ResourcesManager
         */
        Bitmap* addBitmap(string uniqueId, Bitmap* bitmap);

        /**
         * Retrieves a loaded Bitmap by its uniqueId.
         * Returns nullptr whether it isn't already loaded.
         *
         * \return the Bitmap found in the ResouresManager. Nullptr otherwise.
         */
        Bitmap* getBitmap(string uniqueId);

        /**
         * Removes the Bitmap from this ResourcesManager and delete the memory
         * allocated for this Bitmap.
         *
         * \return whether the deletion succeed.
         */
        bool delBitmap(string uniqueId);
        
        /**
         * Removes the Bitmap from this ResourcesManager but contrary to delBitmap(string),
         * it doesn't delete the memory but returns the Bitmap. Returns nullptr whether
         * this uniqueId doesn't refer to any Bitmap.
         *
         * \return the Bitmap removed from the ResourcesManager.
         */
        Bitmap* remBitmap(string uniqueId);

        /**
         * Loads a Sample from a file and adds it to the ResourcesManager.
         *
         * <b>WARNING</b>
         *   - if the uniqueId is already used, the old Sample will be deleted
         *
         * @param uniqueId the unique name given to this Sample
         * @param filepath the path to the sample
         *
         * \return a pointer to the Sample added to the ResourcesManager
         */
        Sample* loadSample(string uniqueId, string filepath);

        /**
         * Adds an existing Sample into the ResourcesManager
         *
         * <b>WARNING</b>
         *  - the memory of the sample will be managed by the ResourcesManager
         *  - if the uniqueId is already used, the old Sample will be deleted
         *
         * @param uniqueId the unique id of this resource
         * @param sample the Sample to delegate to the ResourcesManager
         *
         * \return a pointer to the Sample added to the ResourcesManager
         */
        Sample* addSample(string uniqueId, Sample* sample);

        /**
         * Retrieves a loaded Sample by its uniqueId.
         * Returns nullptr whether it isn't already loaded.
         *
         * \return the Sample found in the ResouresManager. Nullptr otherwise.
         */
        Sample* getSample(string uniqueId);

        /**
         * Removes the Sample from this ResourcesManager and delete the memory
         * allocated for this Sample.
         *
         * \return whether the deletion succeed.
         */
        bool delSample(string uniqueId);
        
        /**
         * Removes the Sample from this ResourcesManager but contrary to delSample(string),
         * it doesn't delete the memory but returns the Sample. Returns nullptr whether
         * this uniqueId doesn't refer to any Sample.
         *
         * \return the Sample removed from the ResourcesManager.
         */
        Sample* remSample(string uniqueId);

        /**
         * Loads a Font from a file and adds it to the ResourcesManager.
         *
         * <b>WARNING</b>
         *   - if the uniqueId is already used, the old Font will be deleted
         *
         * @param uniqueId the unique name given to this Font
         * @param filepath the path to the font
         * @param ptSize the point size to use with this font
         *
         * \return a pointer to the Font added to the ResourcesManager.
         */
        Font* loadFont(string uniqueId, string filepath, int ptSize);

        /**
         * Adds an existing Font into the ResourcesManager
         *
         * <b>WARNING</b>
         *  - the memory of the font will be managed by the ResourcesManager
         *  - if the uniqueId is already used, the old font will be deleted
         *
         * @param uniqueId the unique id of this resource
         * @param sample the Font to delegate to the ResourcesManager
         *
         * \return a pointer to the Font added to the ResourcesManager
         */
        Font* addFont(string uniqueId, Font* sample);

        /**
         * Retrieves a loaded Font by its uniqueId.
         * Returns nullptr whether it isn't already loaded.
         *
         * \return the Font found in the ResouresManager. Nullptr otherwise.
         */
        Font* getFont(string uniqueId);

        /**
         * Removes the Font from this ResourcesManager and delete the memory
         * allocated for this Font.
         *
         * \return whether the deletion succeed.
         */
        bool delFont(string uniqueId);
        
        /**
         * Removes the Font from this ResourcesManager but contrary to delFont(string),
         * it doesn't delete the memory but returns the Font. Returns nullptr whether
         * this uniqueId doesn't refer to any Font.
         *
         * \return the Font removed from the ResourcesManager.
         */
        Font* remFont(string uniqueId);

};


}

#endif // MEH_RESOURCES_MANAGER_H

