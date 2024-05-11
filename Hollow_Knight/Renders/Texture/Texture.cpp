#include "Framework.h"
#include "Texture.h"

map<wstring, Texture*> Texture::textures; // static map 초기화

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
    :srv(srv), image(move(image)) // move라는 함수를 써야 사용가능, 이동생성자라고 불림, 복사를 하지 않고 옮기는 작업을함
{
}

Texture::~Texture()
{
    srv->Release();
}

Texture* Texture::Add(wstring file)
{
    file = L"_Textures/" + file;

    if (textures.count(file) > 0)
        return textures[file];

    ScratchImage image;
    LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    ID3D11ShaderResourceView* tempSRV;

    CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &tempSRV);

    Texture* texture = new Texture(tempSRV, image);

    textures[file] = texture;

    return texture;
}

void Texture::Delete()
{
    for (pair<wstring, Texture*> p : textures)
        delete p.second;
}

void Texture::SetPS(UINT slot)
{
    DC->PSSetShaderResources(slot, 1, &srv);
}

Vector2 Texture::GetSize()
{
    return Vector2(image.GetMetadata().width, image.GetMetadata().height); // 크기가 필요할 일이 생길떄 사용
}
