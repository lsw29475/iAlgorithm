#include <Windows.h>
#include <math.h>
#include "iSha256.h"

void x(long long *e, long long *t)
{
    for (int i = 0; i < 16; i++)
    {
        e[i] = (t[2 * i] + (t[2 * i + 1] << 8)) & 0xFFFF;
    }
    e[15] &= 32767;
}

void b(long long *e, long long *t, long long r)
{
    long long n;
    long long i = ~(r - 1);

    for (int a = 0; a < 16; a++)
    {
        n = i & (e[a] ^ t[a]);
        e[a] ^= n;
        t[a] ^= n;
    }
}

void v(long long *e, long long *t, long long *r)
{
    for (int n = 0; n < 16; n++)
    {
        e[n] = t[n] + r[n];
    }
}

void k(long long *e, long long *t, long long *r)
{
    for (int n = 0; n < 16; n++)
    {
        e[n] = t[n] - r[n];
    }
}

void A(long long *e, long long *t, long long *r)
{
    long long n, i, a = 0, s = 0, o = 0, u = 0, c = 0, f = 0, d = 0, l = 0, h = 0, p = 0, y = 0, b = 0, m = 0, g = 0, w = 0, _ = 0, v = 0, k = 0, A = 0, S = 0, E = 0, P = 0, x = 0, M = 0, C = 0, K = 0, U = 0, R = 0, B = 0, j = 0, T = 0, I = r[0], O = r[1], z = r[2], D = r[3], q = r[4], N = r[5], F = r[6], L = r[7], H = r[8], W = r[9], G = r[10], Z = r[11], V = r[12], Y = r[13], $ = r[14], J = r[15];

    a += (n = t[0]) * I;
    s += n * O;
    o += n * z;
    u += n * D;
    c += n * q;
    f += n * N;
    d += n * F;
    l += n * L;
    h += n * H;
    p += n * W;
    y += n * G;
    b += n * Z;
    m += n * V;
    g += n * Y;
    w += n * $;
    _ += n * J;
    s += (n = t[1]) * I;
    o += n * O;
    u += n * z;
    c += n * D;
    f += n * q;
    d += n * N;
    l += n * F;
    h += n * L;
    p += n * H;
    y += n * W;
    b += n * G;
    m += n * Z;
    g += n * V;
    w += n * Y;
    _ += n * $;
    v += n * J;
    o += (n = t[2]) * I;
    u += n * O;
    c += n * z;
    f += n * D;
    d += n * q;
    l += n * N;
    h += n * F;
    p += n * L;
    y += n * H;
    b += n * W;
    m += n * G;
    g += n * Z;
    w += n * V;
    _ += n * Y;
    v += n * $;
    k += n * J;
    u += (n = t[3]) * I;
    c += n * O;
    f += n * z;
    d += n * D;
    l += n * q;
    h += n * N;
    p += n * F;
    y += n * L;
    b += n * H;
    m += n * W;
    g += n * G;
    w += n * Z;
    _ += n * V;
    v += n * Y;
    k += n * $;
    A += n * J;
    c += (n = t[4]) * I;
    f += n * O;
    d += n * z;
    l += n * D;
    h += n * q;
    p += n * N;
    y += n * F;
    b += n * L;
    m += n * H;
    g += n * W;
    w += n * G;
    _ += n * Z;
    v += n * V;
    k += n * Y;
    A += n * $;
    S += n * J;
    f += (n = t[5]) * I;
    d += n * O;
    l += n * z;
    h += n * D;
    p += n * q;
    y += n * N;
    b += n * F;
    m += n * L;
    g += n * H;
    w += n * W;
    _ += n * G;
    v += n * Z;
    k += n * V;
    A += n * Y;
    S += n * $;
    E += n * J;
    d += (n = t[6]) * I;
    l += n * O;
    h += n * z;
    p += n * D;
    y += n * q;
    b += n * N;
    m += n * F;
    g += n * L;
    w += n * H;
    _ += n * W;
    v += n * G;
    k += n * Z;
    A += n * V;
    S += n * Y;
    E += n * $;
    P += n * J;
    l += (n = t[7]) * I;
    h += n * O;
    p += n * z;
    y += n * D;
    b += n * q;
    m += n * N;
    g += n * F;
    w += n * L;
    _ += n * H;
    v += n * W;
    k += n * G;
    A += n * Z;
    S += n * V;
    E += n * Y;
    P += n * $;
    x += n * J;
    h += (n = t[8]) * I;
    p += n * O;
    y += n * z;
    b += n * D;
    m += n * q;
    g += n * N;
    w += n * F;
    _ += n * L;
    v += n * H;
    k += n * W;
    A += n * G;
    S += n * Z;
    E += n * V;
    P += n * Y;
    x += n * $;
    M += n * J;
    p += (n = t[9]) * I;
    y += n * O;
    b += n * z;
    m += n * D;
    g += n * q;
    w += n * N;
    _ += n * F;
    v += n * L;
    k += n * H;
    A += n * W;
    S += n * G;
    E += n * Z;
    P += n * V;
    x += n * Y;
    M += n * $;
    C += n * J;
    y += (n = t[10]) * I;
    b += n * O;
    m += n * z;
    g += n * D;
    w += n * q;
    _ += n * N;
    v += n * F;
    k += n * L;
    A += n * H;
    S += n * W;
    E += n * G;
    P += n * Z;
    x += n * V;
    M += n * Y;
    C += n * $;
    K += n * J;
    b += (n = t[11]) * I;
    m += n * O;
    g += n * z;
    w += n * D;
    _ += n * q;
    v += n * N;
    k += n * F;
    A += n * L;
    S += n * H;
    E += n * W;
    P += n * G;
    x += n * Z;
    M += n * V;
    C += n * Y;
    K += n * $;
    U += n * J;
    m += (n = t[12]) * I;
    g += n * O;
    w += n * z;
    _ += n * D;
    v += n * q;
    k += n * N;
    A += n * F;
    S += n * L;
    E += n * H;
    P += n * W;
    x += n * G;
    M += n * Z;
    C += n * V;
    K += n * Y;
    U += n * $;
    R += n * J;
    g += (n = t[13]) * I;
    w += n * O;
    _ += n * z;
    v += n * D;
    k += n * q;
    A += n * N;
    S += n * F;
    E += n * L;
    P += n * H;
    x += n * W;
    M += n * G;
    C += n * Z;
    K += n * V;
    U += n * Y;
    R += n * $;
    B += n * J;
    w += (n = t[14]) * I;
    _ += n * O;
    v += n * z;
    k += n * D;
    A += n * q;
    S += n * N;
    E += n * F;
    P += n * L;
    x += n * H;
    M += n * W;
    C += n * G;
    K += n * Z;
    U += n * V;
    R += n * Y;
    B += n * $;
    j += n * J;
    _ += (n = t[15]) * I;
    s += (long long)38 * (k += n * z);
    o += (long long)38 * (A += n * D);
    u += (long long)38 * (S += n * q);
    c += (long long)38 * (E += n * N);
    f += (long long)38 * (P += n * F);
    d += (long long)38 * (x += n * L);
    l += (long long)38 * (M += n * H);
    h += (long long)38 * (C += n * W);
    p += (long long)38 * (K += n * G);
    y += (long long)38 * (U += n * Z);
    b += (long long)38 * (R += n * V);
    m += (long long)38 * (B += n * Y);
    g += (long long)38 * (j += n * $);
    w += (long long)38 * (T += n * J);

    a += (long long)38 * (v += n * O);
    n = a + 1 + 65535;
    a = n - ((long long)65536 * (i = floor((double)n / (double)65536)));

    n = s + i + 65535;
    s = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = o + i + 65535;
    o = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = u + i + 65535;
    u = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = c + i + 65535;
    c = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = f + i + 65535;
    f = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = d + i + 65535;
    d = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = l + i + 65535;
    l = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = h + i + 65535;
    h = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = p + i + 65535;
    p = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = y + i + 65535;
    y = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = b + i + 65535;
    b = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = m + i + 65535;
    m = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = g + i + 65535;
    g = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = w + i + 65535;
    w = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = _ + i + 65535;
    _ = n - (long long)65536 * (i = floor((double)n / (double)65536));

    a += i - 1 + (long long)37 * (i - 1);
    n = a + 1 + 65535;
    a = n - (long long)65536 * (i = floor((double)n / (double)65536));

    n = s + i + 65535;
    s = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = o + i + 65535;
    o = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = u + i + 65535;
    u = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = c + i + 65535;
    c = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = f + i + 65535;
    f = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = d + i + 65535;
    d = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = l + i + 65535;
    l = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = h + i + 65535;
    h = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = p + i + 65535;
    p = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = y + i + 65535;
    y = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = b + i + 65535;
    b = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = m + i + 65535;
    m = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = g + i + 65535;
    g = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = w + i + 65535;
    w = n - (long long)65536 * (i = floor((double)n / (double)65536));
    n = _ + i + 65535;
    _ = n - (long long)65536 * (i = floor((double)n / (double)65536));

    a += i - 1 + (long long)37 * (i - 1);
    e[0] = a;
    e[1] = s;
    e[2] = o;
    e[3] = u;
    e[4] = c;
    e[5] = f;
    e[6] = d;
    e[7] = l;
    e[8] = h;
    e[9] = p;
    e[10] = y;
    e[11] = b;
    e[12] = m;
    e[13] = g;
    e[14] = w;
    e[15] = _;
}

void S(long long *e, long long *t)
{
    A(e, t, t);
}

void E(long long *e, long long *t)
{
    long long i[16] = {0x00};

    for (int n = 0; n < 16; n++)
    {
        i[n] = t[n];
    }

    for (int n = 253; n >= 0; n--)
    {
        S(i, i);
        if (n != 2 && n != 4)
        {
            A(i, i, t);
        }
    }

    for (int n = 0; n < 16; n++)
    {
        e[n] = i[n];
    }
}

void y(long long *e)
{
    long long r;
    long long n = 1;

    for (int t = 0; t < 16; t++)
    {
        r = e[t] + n + 65535;
        n = floor((double)r / (double)65536);
        e[t] = r - 65536 * n;
    }

    e[0] += n - 1 + 37 * (n - 1);
}

void m(long long *e, long long *t)
{
    long long s[16] = {0x00};
    long long o[16] = {0x00};
    long long a;

    for (int n = 0; n < 16; n++)
    {
        o[n] = t[n];
    }

    y(o);
    y(o);
    y(o);

    for (int i = 0; i < 2; i++)
    {
        s[0] = o[0] - 65517;
        for (int n = 1; n < 15; n++)
        {
            s[n] = o[n] - 65535 - (s[n - 1] >> 16 & 1);
            s[n - 1] &= 65535;
        }
        s[15] = o[15] - 32767 - (s[14] >> 16 & 1);
        a = s[15] >> 16 & 1;
        s[14] &= 65535;
        b(o, s, 1 - a);
    }

    for (int n = 0; n < 16; n++)
    {
        e[2 * n] = 255 & o[n];
        e[2 * n + 1] = o[n] >> 8;
    }
}

void scalar_multi(long long *e, long long *t, long long *n)
{
    long long s[32] = {0x00};
    long long u[80] = {0x00};

    long long f[16] = {0x00};
    long long l[16] = {0x00};
    long long c[16] = {0x00};
    long long d[16] = {0x00};
    long long h[16] = {0x00};
    long long p[16] = {0x00};

    long long o[32] = {56129, 1};

    long long y[48] = {0x00};
    long long g[64] = {0x00};

    long long i = 0;

    for (int i = 0; i < 32; i++)
    {
        s[i] = t[i];
    }
    s[31] = (t[31] & 127) | 64;
    s[0] &= 248;

    x(u, n);
    for (int i = 0; i < 16; i++)
    {
        f[i] = u[i];
        l[i] = c[i] = d[i] = 0;
    }

    c[0] = 1;
    l[0] = 1;

    for (int a = 254; a >= 0; --a)
    {
        i = (s[a >> 3] >> (7 & a)) & 1;
        b(c, f, i);
        b(d, l, i);
        v(h, c, d);
        k(c, c, d);
        v(d, f, l);
        k(f, f, l);
        S(l, h);
        S(p, c);
        A(c, d, c);
        A(d, f, h);
        v(h, c, d);
        k(c, c, d);
        S(f, c);
        k(d, l, p);
        A(c, d, o);
        v(c, c, l);
        A(d, d, c);
        A(c, l, p);
        A(l, f, u);
        S(f, h);
        b(c, f, i);
        b(d, l, i);
    }

    memcpy(u + 16, c, sizeof(c));
    memcpy(u + 32, d, sizeof(d));
    memcpy(u + 48, f, sizeof(f));
    memcpy(u + 64, l, sizeof(l));

    memcpy(y, u + 32, sizeof(y));
    memcpy(g, u + 16, sizeof(g));

    E(y, y);
    A(g, g, y);
    m(e, g);
}

void build_ecdh_param(unsigned char *ecdh_param, unsigned char *oid, unsigned char *hash_algorithm, unsigned char *cipher_algorithm, unsigned char *fingerprint)
{
    unsigned char magic[20] = {
        0x41, 0x6E, 0x6F, 0x6E, 0x79, 0x6D, 0x6F, 0x75, 0x73, 0x20, 0x53, 0x65, 0x6E, 0x64, 0x65, 0x72,
        0x20, 0x20, 0x20, 0x20};

    memcpy(ecdh_param, oid, 11);
    memcpy(ecdh_param + 11, hash_algorithm, 4);
    memcpy(ecdh_param + 15, cipher_algorithm, 1);
    memcpy(ecdh_param + 16, magic, sizeof(magic));
    memcpy(ecdh_param + 16 + sizeof(magic), fingerprint, 20);
}

void wrap(unsigned char *key, unsigned char *data)
{
    unsigned char iv[8] = {0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6, 0xA6};
    unsigned char t[32] = {0x00};

    for (int j = 5; j >= 0; --j)
    {
        for (int i = 4; i >= 0; --i)
        {
            t[1] = 5 * j + (i + 1);
        }
    }
}

int main(int argc, char **argv)
{
    long long secret_big_num[32];
    long long public_big_num[32];
    long long shared_key[32];
    unsigned char ecdh_param[128];
    unsigned char hash_data[256];
    unsigned char hash_value[256];

    unsigned char public_key[32] = {
        0x74, 0x46, 0x69, 0xB6, 0xDE, 0x9A, 0x5C, 0x7E, 0xD5, 0xE7, 0x2C, 0xA1, 0x27, 0x7C, 0x48, 0xEC,
        0x8C, 0x4A, 0x83, 0x75, 0x5E, 0xC9, 0xC4, 0xEC, 0x49, 0x2F, 0xD9, 0xEF, 0x8F, 0xCD, 0xEF, 0x57};
    unsigned char secret_key[32] = {
        0x59, 0x5D, 0xF3, 0xC1, 0xE3, 0x4E, 0x77, 0xE2, 0x29, 0x92, 0xD0, 0x32, 0x5F, 0x1A, 0x6A, 0x0C,
        0xEF, 0xF4, 0x5B, 0x03, 0x7A, 0x70, 0xBD, 0x09, 0x41, 0x6A, 0x8B, 0xD7, 0xDA, 0xFA, 0xD8, 0xF0};

    unsigned char oid[11] = {
        0x0A, 0x2B, 0x06, 0x01, 0x04, 0x01, 0x97, 0x55, 0x01, 0x05, 0x01};

    unsigned char fingerprint[20] = {
        0xAF, 0x0F, 0x97, 0x3A, 0x31, 0x2F, 0xE9, 0xB7, 0x8C, 0x03, 0x65, 0x70, 0x10, 0x65, 0x7E, 0xD0,
        0x35, 0x9F, 0xBC, 0x2B};

    unsigned char enc_data[48] = {
        0x49, 0xCA, 0x66, 0x0B, 0xC7, 0x94, 0x05, 0x1E, 0x0B, 0x62, 0x8C, 0xC8, 0x34, 0xFC, 0x75, 0x01,
        0x73, 0xED, 0xE5, 0xB0, 0xF9, 0x64, 0x9C, 0x89, 0xB9, 0xDF, 0x99, 0xFF, 0xE7, 0xD3, 0x9C, 0x1C,
        0xB3, 0xF2, 0xE6, 0x40, 0x43, 0xD8, 0xFA, 0x64, 0x45, 0x3C, 0x0D, 0xAE, 0x57, 0x79, 0x73, 0x97};

    unsigned char cipher_algorithm[1] = {0x7};
    unsigned char hash_algorithm[4] = {0x12, 0x03, 0x01, 0x8};

    unsigned char magic[4] = {0x00, 0x00, 0x00, 0x01};

    CSHA256 Sha256;

    for (int i = 0; i < 16; i++)
    {
        unsigned char temp = secret_key[i];
        secret_key[i] = secret_key[31 - i];
        secret_key[31 - i] = temp;
    }

    for (int i = 0; i < 32; i++)
    {
        public_big_num[i] = public_key[i];
    }

    for (int i = 0; i < 32; i++)
    {
        secret_big_num[i] = secret_key[i];
    }

    scalar_multi(shared_key, secret_big_num, public_big_num);
    memset(ecdh_param, 0x00, sizeof(ecdh_param));
    build_ecdh_param(ecdh_param, oid, hash_algorithm, cipher_algorithm, fingerprint);

    for (int i = 0; i < 3; i++)
    {
        memset(hash_data, 0x00, sizeof(hash_data));
        memcpy(hash_data, magic, sizeof(magic));
        for (int j = 0; j < 32; j++)
        {
            hash_data[sizeof(magic) + j] = shared_key[j];
        }
        memcpy(hash_data + sizeof(magic) + 32, ecdh_param, 56);

        memset(hash_value, 0x00, sizeof(hash_value));
        Sha256.InitHash();
        Sha256.CalcHash(hash_data, 92, hash_value);

        wrap(hash_value, enc_data);
    }

    return 0;
}