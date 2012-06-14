/*
* ModSecurity for Apache 2.x, http://www.modsecurity.org/
* Copyright (c) 2004-2011 Trustwave Holdings, Inc. (http://www.trustwave.com/)
*
* You may not use this file except in compliance with
* the License.  You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* If any of the files related to licensing are missing or if you have any
* other questions related to licensing please contact Trustwave Holdings, Inc.
* directly using the email address security@modsecurity.org.
*/

#ifndef __MSC_TREE_H__
#define __MSC_TREE_H__

#include "modsecurity.h"

#define IPV4_TREE 0x1
#define IPV6_TREE 0x2

#define IPV4_LEN 0x20
#define IPV6_LEN 0x80

#define TREE_CHECK(x, y) ((x) & (y))
#define MASK_BITS(x) ((x + 1) * 8)
#define SHIFT_LEFT_MASK(x) (-1 << x)
#define SHIFT_RIGHT_MASK(x,y) (x >> y)

#define NETMASK_256 0x100
#define NETMASK_128 0x80
#define NETMASK_64  0x40
#define NETMASK_32 0x20
#define NETMASK_16 0x10
#define NETMASK_8  0x8
#define NETMASK_4  0x4
#define NETMASK_2  0x2

typedef struct CPTData_ {
    uint8_t netmask;
    struct CPTData_ *next;
} CPTData;

typedef struct TreePrefix_ {
    uint8_t *buffer;
    uint16_t bitlen;
    CPTData *prefix_data;
} TreePrefix;

typedef struct TreeNode_ {
    uint16_t bit;
    int count;
    uint8_t *netmasks;
    TreePrefix *prefix;
    struct TreeNode_ *left, *right;
    struct TreeNode_ *parent;
} TreeNode;

typedef struct CPTTree_ {
    int count;
    apr_pool_t *pool;
    TreeNode *head;
} CPTTree;

typedef struct TreeRoot_ {
    CPTTree *ipv4_tree;
    CPTTree *ipv6_tree;
} TreeRoot;

DSOLOCAL CPTTree *CPTCreateRadixTree(apr_pool_t *pool);
DSOLOCAL TreeNode *CPTIpMatch(modsec_rec *, uint8_t *, CPTTree *, int);
DSOLOCAL TreeNode *TreeAddIP(const char *, CPTTree *, int);

#endif /*__MSC_TREE_H__ */