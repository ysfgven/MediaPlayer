//
// Created by yusuf on 21.05.2026.
//
#include "MetadataReader.h"
#include "MediaFile.h"
#include <taglib/fileref.h>

void MetadataReader::load(MediaFile &file) {
    TagLib::FileRef fileRef(file.getFilePath().wstring().c_str());

    if (fileRef.isNull())
        return;

    TagLib::Tag *tag = fileRef.tag();

    if (tag == nullptr)
        return;
    if (fileRef.audioProperties() == nullptr)
        return;
    file.setTitle(tag->title().to8Bit(true));
    file.setArtist(tag->artist().to8Bit(true));
    file.setDuration(fileRef.audioProperties()->lengthInSeconds());




}
