#include "ImageLoader.hpp"

/// @brief counter of loaded textures
int loaded_texture_cou=0;

/// @brief allocated memory for texture loading
ACD::TextureInfo loaded_textures[DRUM_IMAGES_AMOUNT];

/// @brief Provides reference to copy textures in modules
/// @return pointer to array
ACD::TextureInfo *ACD::GetArrBegin()
{
    //Hit if not enough images loaded
    assert(DRUM_IMAGES_AMOUNT==loaded_texture_cou);
    return &loaded_textures[0];
}

/// @brief Automaticaly load all assigned images
void ACD::LoadDrumImages()
{
    LoadImage(BAR_IMG, BAR_SCORE);
    LoadImage(BELL_IMG, BELL_SCORE);
    LoadImage(CHERRY_IMG, CHERRY_SCORE);
    LoadImage(DOLLAR_IMG, DOLLAR_SCORE);
    LoadImage(LEMON_IMG, LEMON_SCORE);
    LoadImage(ORANGE_IMG, ORANGE_SCORE);
    LoadImage(PLUM_IMG, PLUM_SCORE);
    LoadImage(SEVEN_IMG, SEVEN_SCORE);
    LoadImage(WATERMELLON_IMG, WATERMELLON_SCORE);
    
}


/// @brief Load required texture
/// @param path path to file
/// @param symb_score score of this symbol
void ACD::LoadImage(const char *path, float symb_score)
{
    //Load texture
    TextureInfo buff;
    assert(loaded_texture_cou<DRUM_IMAGES_AMOUNT);
    bool ret = LoadTextureFromFile(path, &buff.texture_data, &buff.texture_width, &buff.texture_height);

    //Check, if texture loaded properly
    assert(ret);
    assert(buff.texture_data!=0);

    //store loaded texture
    buff.score=symb_score;

    loaded_textures[loaded_texture_cou]=buff;

    loaded_texture_cou++;
}

/// @brief Stores loaded texture from RAM to VRAM
/// @param data raw texture
/// @param data_size sie of raw texture
/// @param out_texture pointer to stored texture
/// @param out_width texture width
/// @param out_height texture height
/// @return true if succeed, false otherwise
bool ACD::LoadTextureFromMemory(const void *data, size_t data_size, GLuint *out_texture, int *out_width, int *out_height)
{
    // Load from file
    int image_width = 0;
    int image_height = 0;
    unsigned char* image_data = stbi_load_from_memory((const unsigned char*)data, (int)data_size, &image_width, &image_height, NULL, 4);
    if (image_data == NULL)
        return false;

    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload pixels into texture
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data);

    *out_texture = image_texture;
    *out_width = image_width;
    *out_height = image_height;

    return true;
}


/// @brief Load texture from file to RAM
/// @param file_name texture file name
/// @param out_texture pointer to texture in VRAM
/// @param out_width texture width
/// @param out_height texture height
/// @return true if succeed, false otherwise
bool ACD::LoadTextureFromFile(const char* file_name, GLuint* out_texture, int* out_width, int* out_height)
{
    FILE* f = fopen(file_name, "rb");
    if (f == NULL)
        return false;
    fseek(f, 0, SEEK_END);
    size_t file_size = (size_t)ftell(f);
    if (file_size == -1)
        return false;
    fseek(f, 0, SEEK_SET);
    void* file_data = malloc(file_size);
    fread(file_data, 1, file_size, f);
    bool ret = LoadTextureFromMemory(file_data, file_size, out_texture, out_width, out_height);
    free(file_data);
    return ret;
}