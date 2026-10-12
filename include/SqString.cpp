#include "SqString.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

static int AllocateString(int len, char **buffer) {
    if (!buffer || len < 0 || len == INT_MAX) {
        return ERROR;
    }

    char *data = (char *)malloc((size_t)len + 1);
    if (!data) {
        return ERROR;
    }
    data[len] = '\0';
    *buffer = data;
    return OK;
}

static int IsInitialized(const SqString *S) {
    return S && S->ch && S->len >= 0 && S->capacity > S->len;
}

int InitString(SqString *S) {
    if (!S) {
        return ERROR;
    }

    char *data;
    if (AllocateString(0, &data) != OK) {
        return ERROR;
    }
    S->ch = data;
    S->len = 0;
    S->capacity = 1;
    return OK;
}

void DestroyString(SqString *S) {
    if (S) {
        free(S->ch);
        S->ch = NULL;
        S->len = 0;
        S->capacity = 0;
    }
}

int ClearString(SqString *S) {
    if (!IsInitialized(S)) {
        return ERROR;
    }
    S->len = 0;
    S->ch[0] = '\0';
    return OK;
}

int StrAssign(SqString *S, const char *chars) {
    if (!IsInitialized(S) || !chars) {
        return ERROR;
    }

    size_t length = strlen(chars);
    if (length >= (size_t)INT_MAX) {
        return ERROR;
    }

    char *data;
    if (AllocateString((int)length, &data) != OK) {
        return ERROR;
    }
    memcpy(data, chars, length);

    free(S->ch);
    S->ch = data;
    S->len = (int)length;
    S->capacity = S->len + 1;
    return OK;
}

int StrCopy(SqString *T, const SqString *S) {
    if (!IsInitialized(T) || !IsInitialized(S)) {
        return ERROR;
    }
    return StrAssign(T, S->ch);
}

int StrEmpty(const SqString *S) {
    if (!IsInitialized(S)) {
        return WARNING;
    }
    return S->len == 0 ? TRUE : FALSE;
}

int StrLength(const SqString *S) {
    if (!IsInitialized(S)) {
        return WARNING;
    }
    return S->len;
}

int StrCompare(const SqString *S, const SqString *T) {
    if (!IsInitialized(S) || !IsInitialized(T)) {
        return WARNING;
    }

    int commonLen = S->len < T->len ? S->len : T->len;
    int result = memcmp(S->ch, T->ch, (size_t)commonLen);
    if (result != 0) {
        return result < 0 ? -1 : 1;
    }
    if (S->len == T->len) {
        return 0;
    }
    return S->len < T->len ? -1 : 1;
}

int Concat(SqString *T, const SqString *S1, const SqString *S2) {
    if (!IsInitialized(T) || !IsInitialized(S1) || !IsInitialized(S2)
        || S1->len > INT_MAX - S2->len) {
        return ERROR;
    }

    int len = S1->len + S2->len;
    char *data;
    if (AllocateString(len, &data) != OK) {
        return ERROR;
    }
    memcpy(data, S1->ch, (size_t)S1->len);
    memcpy(data + S1->len, S2->ch, (size_t)S2->len);

    free(T->ch);
    T->ch = data;
    T->len = len;
    T->capacity = len + 1;
    return OK;
}

int SubString(SqString *Sub, const SqString *S, int pos, int len) {
    if (!IsInitialized(Sub) || !IsInitialized(S) || pos < 1 || len < 0
        || pos > S->len + 1 || len > S->len - (pos - 1)) {
        return ERROR;
    }

    char *data;
    if (AllocateString(len, &data) != OK) {
        return ERROR;
    }
    memcpy(data, S->ch + pos - 1, (size_t)len);

    free(Sub->ch);
    Sub->ch = data;
    Sub->len = len;
    Sub->capacity = len + 1;
    return OK;
}

int Index(const SqString *S, const SqString *T, int pos) {
    if (!IsInitialized(S) || !IsInitialized(T) || pos < 1 || pos > S->len + 1) {
        return WARNING;
    }
    if (T->len == 0) {
        return pos;
    }
    if (T->len > S->len - (pos - 1)) {
        return 0;
    }

    for (int i = pos - 1; i <= S->len - T->len; i++) {
        if (memcmp(S->ch + i, T->ch, (size_t)T->len) == 0) {
            return i + 1;
        }
    }
    return 0;
}

int StrInsert(SqString *S, int pos, const SqString *T) {
    if (!IsInitialized(S) || !IsInitialized(T) || pos < 1 || pos > S->len + 1
        || S->len > INT_MAX - T->len) {
        return ERROR;
    }

    int len = S->len + T->len;
    char *data;
    if (AllocateString(len, &data) != OK) {
        return ERROR;
    }

    int offset = pos - 1;
    memcpy(data, S->ch, (size_t)offset);
    memcpy(data + offset, T->ch, (size_t)T->len);
    memcpy(data + offset + T->len, S->ch + offset, (size_t)(S->len - offset));

    free(S->ch);
    S->ch = data;
    S->len = len;
    S->capacity = len + 1;
    return OK;
}

int StrDelete(SqString *S, int pos, int len) {
    if (!IsInitialized(S) || pos < 1 || len < 0 || pos > S->len + 1
        || len > S->len - (pos - 1)) {
        return ERROR;
    }

    int offset = pos - 1;
    memmove(S->ch + offset, S->ch + offset + len,
            (size_t)(S->len - offset - len) + 1);
    S->len -= len;
    return OK;
}

int Replace(SqString *S, const SqString *T, const SqString *V) {
    if (!IsInitialized(S) || !IsInitialized(T) || !IsInitialized(V) || T->len == 0) {
        return ERROR;
    }

    int occurrences = 0;
    for (int i = 0; i <= S->len - T->len;) {
        if (memcmp(S->ch + i, T->ch, (size_t)T->len) == 0) {
            occurrences++;
            i += T->len;
        } else {
            i++;
        }
    }
    if (occurrences == 0) {
        return OK;
    }

    int delta = V->len - T->len;
    if ((delta > 0 && occurrences > (INT_MAX - S->len) / delta)
        || (delta < 0 && occurrences > S->len / -delta)) {
        return ERROR;
    }
    int newLen = S->len + occurrences * delta;
    char *data;
    if (AllocateString(newLen, &data) != OK) {
        return ERROR;
    }

    int src = 0;
    int dst = 0;
    while (src < S->len) {
        if (src <= S->len - T->len
            && memcmp(S->ch + src, T->ch, (size_t)T->len) == 0) {
            memcpy(data + dst, V->ch, (size_t)V->len);
            src += T->len;
            dst += V->len;
        } else {
            data[dst++] = S->ch[src++];
        }
    }
    data[newLen] = '\0';

    free(S->ch);
    S->ch = data;
    S->len = newLen;
    S->capacity = newLen + 1;
    return OK;
}
