/******************************************************************************
* Copyright (c) 2018(-2024) STMicroelectronics.
* All rights reserved.
*
* This file is part of the TouchGFX 4.24.2 distribution.
*
* This software is licensed under terms that can be found in the LICENSE file in
* the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
*******************************************************************************/

/**
 * @file touchgfx/Texts.hpp
 *
 * Declares the touchgfx::Texts class.
 */
#ifndef TOUCHGFX_TEXTS_HPP
#define TOUCHGFX_TEXTS_HPP

#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/Types.hpp>

namespace touchgfx
{
/** Language IDs generated by the text converter are uint16_t typedef'ed. */
typedef uint16_t LanguageId;

/**
 * Class for setting language and getting texts. The language set will determine which texts
 * will be used in the application.
 */
class Texts
{
public:
    /**
     * Sets the current language for texts.
     *
     * @param  id The id of the language.
     */
    static void setLanguage(LanguageId id);

    /**
     * Gets the current language.
     *
     * @return The id of the language.
     */
    static LanguageId getLanguage()
    {
        return currentLanguage;
    }

    /**
     * Get text in the set language.
     *
     * @param  id The id of the text to lookup.
     *
     * @return The text.
     *
     * @see setLanguage
     */
    const Unicode::UnicodeChar* getText(TypedTextId id) const;

    /**
     * Adds or replaces a translation. This function allows an application to add a
     * translation at runtime.
     *
     * @param  id          The id of the language to add or replace.
     * @param  translation A pointer to the translation in flash or RAM.
     */
    static void setTranslation(LanguageId id, const void* translation);

private:
    static LanguageId currentLanguage;
};

} // namespace touchgfx

#endif // TOUCHGFX_TEXTS_HPP
