#include "packer.hpp"

#include <command/Log.hpp>
#include <nuspack/packaging/NUSPackage.hpp>



PackError createPackage(const fspath& dirPath, const fspath& out, const Key& encryptionKey, const Key& encryptKeyWith) {
    AppInfo info;
    if(!info.parseFromXML(dirPath / "code/app.xml")) LOG_ERR_AND_RETURN(PackError::XML_ERROR);

    const uint64_t parentID = info.titleID & ~0x0000000F00000000;

    const ContentRules rules = getCommonRules(info.groupID, parentID);

    PackageConfig config(dirPath, info, encryptionKey, encryptKeyWith, rules);
    NUSPackage package(config);
    package.PackContents(out);

    return PackError::NONE;
}

std::string packErrorGetName(PackError err) {
    switch(err) {
        case PackError::NONE:
            return "NONE";
        case PackError::XML_ERROR:
            return "XML_ERROR";
        default:
            return "UNKNOWN";
    }
}
