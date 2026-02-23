typedef struct CheckerTexture CheckerTexture;
static Color3 checker_texture_value(const CheckerTexture *c, float u, float v, Point3 p);

typedef enum {
  TEXTURE_SOLID_COLOR,
  TEXTURE_CHECKER,
} TextureType;

typedef struct {
  TextureType type;
  union {
    SolidColor solid_color;
    CheckerTexture *checker_texture;
  } u;
} Texture;

static Color3 texture_color_value(Texture *t, float u, float v, Point3 p) {
  switch (t->type) {
    case TEXTURE_SOLID_COLOR:
      return solid_color_value(&t->u.solid_color, u, v, p);
    case TEXTURE_CHECKER:
      return checker_texture_value(t->u.checker_texture, u, v, p);
    default:
      assert(false && "Unknown Texture");
  }
}
