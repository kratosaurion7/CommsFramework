#include "BaseFont.h"

#include "Graphic/Base Classes/BaseTexture.h"

BaseFont::BaseFont()
{
    GlyphMap = NULL;

    FontType = FontTypes::FONT_FILE;
}

BaseFont::~BaseFont()
{
    if (GlyphMap != NULL)
    {
        GlyphMap->Clear();
        delete(GlyphMap);
    }
}

void BaseFont::LoadSpriteFont(BaseTexture* fontTexture, SpriteFontGlyph** glyphs, int charactersCount)
{
    GlyphMap = new PointerList<Pair<const char*, BaseTexture*>*>();

    for (int i = 0; i < charactersCount; i++)
    {
        SpriteFontGlyph* glyph = glyphs[i];

        FRectangle rec = FRectangle(glyph->X, glyph->Y, glyph->H, glyph->W);
        
        BaseTexture* subTex = fontTexture->GetSubTexture(rec);

        Pair<const char*, BaseTexture*>* newGlyphPair = new Pair<const char*, BaseTexture*>();
        newGlyphPair->Item1 = glyph->Value;
        newGlyphPair->Item2 = subTex;

        this->GlyphMap->Add(newGlyphPair);
    }

    FontType = SPRITE_FONT;
}

SpriteFontGlyph** BaseFont::BuildDefaultFontGlyphDescriptor(int & outLength)
{
    int defaultCharacterAmount = 26;

    SpriteFontGlyph** ret = new SpriteFontGlyph*[defaultCharacterAmount];

    SpriteFontGlyph* a = new SpriteFontGlyph();
    a->Value = "a";
    a->H = 183;
    a->W = 172;
    a->X = 6;
    a->Y = 4;
    ret[0] = a;
    
    SpriteFontGlyph* b = new SpriteFontGlyph();
    b->Value = "b";
    b->H = 183;
    b->W = 142;
    b->X = 194;
    b->Y = 4;
    ret[1] = b;

    SpriteFontGlyph* c = new SpriteFontGlyph();
    c->Value = "c";
    c->H = 189;
    c->W = 164;
    c->X = 360;
    c->Y = 1;
    ret[2] = c;

    SpriteFontGlyph* d = new SpriteFontGlyph();
    d->Value = "d";
    d->H = 185;
    d->W = 155;
    d->X = 551;
    d->Y = 3;
    ret[3] = d;

    SpriteFontGlyph* e = new SpriteFontGlyph();
    e->Value = "e";
    e->H = 185;
    e->W = 140;
    e->X = 737;
    e->Y = 3;
    ret[4] = e;

    SpriteFontGlyph* f = new SpriteFontGlyph();
    f->Value = "f";
    f->H = 185;
    f->W = 126;
    f->X = 909;
    f->Y = 3;
    ret[5] = f;

    SpriteFontGlyph* g = new SpriteFontGlyph();
    g->Value = "g";
    g->H = 191;
    g->W = 172;
    g->X = 1058;
    g->Y = 0;
    ret[6] = g;

    SpriteFontGlyph* h = new SpriteFontGlyph();
    h->Value = "h";
    h->H = 185;
    h->W = 147;
    h->X = 1263;
    h->Y = 3;
    ret[7] = h;

    SpriteFontGlyph* i = new SpriteFontGlyph();
    i->Value = "i";
    i->H = 185;
    i->W = 27;
    i->X = 1452;
    i->Y = 3;
    ret[8] = i;

    SpriteFontGlyph* j = new SpriteFontGlyph();
    j->Value = "j";
    j->H = 188;
    j->W = 103;
    j->X = 1507;
    j->Y = 3;
    ret[9] = j;

    SpriteFontGlyph* k = new SpriteFontGlyph();
    k->Value = "k";
    k->H = 185;
    k->W = 154;
    k->X = 1645;
    k->Y = 3;
    ret[10] = k;

    SpriteFontGlyph* l = new SpriteFontGlyph();
    l->Value = "l";
    l->H = 185;
    l->W = 117;
    l->X = 1817;
    l->Y = 3;
    ret[11] = l;

    SpriteFontGlyph* m = new SpriteFontGlyph();
    m->Value = "m";
    m->H = 185;
    m->W = 178;
    m->X = 1959;
    m->Y = 3;
    ret[12] = m;

    SpriteFontGlyph* n = new SpriteFontGlyph();
    n->Value = "n";
    n->H = 185;
    n->W = 149;
    n->X = 2172;
    n->Y = 3;
    ret[13] = n;

    SpriteFontGlyph* o = new SpriteFontGlyph();
    o->Value = "o";
    o->H = 191;
    o->W = 179;
    o->X = 2350;
    o->Y = 0;
    ret[14] = o;

    SpriteFontGlyph* p = new SpriteFontGlyph();
    p->Value = "p";
    p->H = 185;
    p->W = 143;
    p->X = 2557;
    p->Y = 3;
    ret[15] = p;

    SpriteFontGlyph* q = new SpriteFontGlyph();
    q->Value = "q";
    q->H = 194;
    q->W = 181;
    q->X = 2720;
    q->Y = 0;
    ret[16] = q;

    SpriteFontGlyph* r = new SpriteFontGlyph();
    r->Value = "r";
    r->H = 185;
    r->W = 164;
    r->X = 2927;
    r->Y = 0;
    ret[17] = r;

    SpriteFontGlyph* s = new SpriteFontGlyph();
    s->Value = "s";
    s->H = 191;
    s->W = 149;
    s->X = 3103;
    s->Y = 0;
    ret[18] = s;

    SpriteFontGlyph* t = new SpriteFontGlyph();
    t->Value = "t";
    t->H = 186;
    t->W = 150;
    t->X = 3268;
    t->Y = 2;
    ret[19] = t;

    SpriteFontGlyph* u = new SpriteFontGlyph();
    u->Value = "u";
    u->H = 189;
    u->W = 148;
    u->X = 3439;
    u->Y = 2;
    ret[20] = u;

    SpriteFontGlyph* v = new SpriteFontGlyph();
    v->Value = "v";
    v->H = 186;
    v->W = 171;
    v->X = 3605;
    v->Y = 2;
    ret[21] = v;

    SpriteFontGlyph* w = new SpriteFontGlyph();
    w->Value = "w";
    w->H = 186;
    w->W = 240;
    w->X = 3778;
    w->Y = 2;
    ret[22] = w;

    SpriteFontGlyph* x = new SpriteFontGlyph();
    x->Value = "x";
    x->H = 186;
    x->W = 170;
    x->X = 4018;
    x->Y = 2;
    ret[23] = x;

    SpriteFontGlyph* y = new SpriteFontGlyph();
    y->Value = "y";
    y->H = 186;
    y->W = 170;
    y->X = 4188;
    y->Y = 2;
    ret[24] = y;

    SpriteFontGlyph* z = new SpriteFontGlyph();
    z->Value = "z";
    z->H = 186;
    z->W = 149;
    z->X = 4362;
    z->Y = 2;
    ret[25] = z;


    outLength = defaultCharacterAmount;

    return ret;
}