#ifndef WARBLER_PREPROCESSOR_H
#define WARBLER_PREPROCESSOR_H

/**
 * @brief Strip comments from Warbler source file.
 * 
 * Comments will be stripped while preserving newlines.
 * Block comments will be replaced by spaces
 * 
 * @param src 
 */
void preprocess(char *src);

#endif
