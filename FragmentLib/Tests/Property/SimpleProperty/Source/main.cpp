#include <Fragment/Fragment.h>
#include <stdlib.h>
#include <stdio.h>
using namespace Fragment;

#ifdef _DEBUG
#pragma comment(lib, "FragmentLib_d.lib")
#else
#pragma comment(lib, "FragmentLib.lib")
#endif

class ITexture : public IUnknown
{
public:
};

FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(Texture);

class IGeometry : public IUnknown
{
public:
};

FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(Geometry);

class IGraphics : public IUnknown
{
public:
	void Initialize()
	{
		for(unsigned long i = 0; i < 8; i++)
		{
			Textures[i].Graphics = GetMemoryList()->Find(this);
		};
		Geometry.Graphics = GetMemoryList()->Find(this);
	};
	void BindTexture(const CTexture &Texture)
	{
		printf("Binding texture '%i'\n", Texture.Handle());
	};
	void DrawGeometry(const CGeometry &_Geometry)
	{
		printf("Drawing Geometry '%i'\n", _Geometry.Handle());
	};
	class ITextureBind : public IProperty<CTexture>
	{
	private:
		friend class IGraphics;
		Object<IGraphics> Graphics;
		CTexture Texture;
		void OnEqual(const CTexture &Object)
		{
			this->Texture = Object;
			Graphics->BindTexture(Texture);
		};
		void OnPlusEqual(const CTexture &Object) {};
		void OnMinusEqual(const CTexture &Object) {};
		void OnMultEqual(const CTexture &Object) {};
		void OnDivEqual(const CTexture &Object) {};
	public:
		using IProperty<CTexture>::operator=;
	}Textures[8];

	class IGeometryBind : public IProperty<CGeometry>
	{
	private:
		friend class IGraphics;
		Object<IGraphics> Graphics;
		CGeometry Geometry;
		void OnEqual(const CGeometry &Object) {};
		void OnPlusEqual(const CGeometry &Object)
		{
			Graphics->DrawGeometry(Object);
		};
		void OnMinusEqual(const CGeometry &Object) {};
		void OnMultEqual(const CGeometry &Object) {};
		void OnDivEqual(const CGeometry &Object) {};
	public:
	}Geometry;
};

FRAGMENTLIB_DECLARE_OBJECT_INTERFACES(Graphics);

int main(int argc, char **argv)
{
	printf("Initializing test.\n");
	CreateDefaultMemoryList();
	CGraphics Graphics(new IGraphics);
	CGeometry Geometry(new IGeometry);
	CTexture Texture(new ITexture);
	Graphics->Initialize();
	printf("Starting test.\n");
	Graphics->Textures[0] = Texture;
	Graphics->Geometry += Geometry;
	printf("End of test. Press any key to continue.\n");
	getchar();
	return 0;
};
