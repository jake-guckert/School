/*
 * UTAH image format
 * Copyright (c) 2013 Jake Guckert & Josh Bell 
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

//#define DEBUG

#include "libavutil/bprint.h"
#include "libavutil/imgutils.h"
#include "avcodec.h"
#include "bytestream.h"
#include "internal.h"
#include "png.h"
#include "pngdsp.h"

/* TODO:
 * - add 16 bit depth support
 */
#include <zlib.h>

//#define DEBUG
typedef struct UTAHDecContext 
{
    AVFrame picture;
} UTAHDecContext;

static int decode_frame(AVCodecContext *avctx,
                        void *data, int *got_frame,
                        AVPacket *avpkt)
{
    UTAHDecContext * const s = avctx->priv_data;
    const uint8_t *buf      = avpkt->data;
    AVFrame *picture        = data;
    AVFrame *p;
    uint32_t head;
    int ret, width, height;

    p = &s->picture;

    //get out UTAH from buffer
    for(int i=0; i < 4; i++)
      head = bytestream_get_byte(&buf);

    //get width and height and set as parameters for AVCodecContext
    width = bytestream_get_le32(&buf);
    height = bytestream_get_le32(&buf);
    avctx->width = width;
    avctx->height = height;
    avctx->pix_fmt = AV_PIX_FMT_RGB8;

    //set up frame
    if ((ret = ff_get_buffer(avctx, p)) < 0) {
        av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
        return ret;
    }
    p->reference=0;
    p->pict_type = AV_PICTURE_TYPE_I;
    p->key_frame = 1;

    //Move data from file to a frame
    for (int row = 0; row < height; row++)
      for (int col = 0; col < width; col++)
      {
	uint8_t *pixel = p->data[0] + row * p->linesize[0] + col;
	pixel[0] = bytestream_get_byte(&buf);
      }

    *picture = s->picture;
    *got_frame = 1;
    
    return ret;
}

static av_cold int utah_dec_init(AVCodecContext *avctx)
{
    UTAHDecContext *s = avctx->priv_data;

    avcodec_get_frame_defaults(&s->picture);
    avctx->coded_frame = &s->picture;

    return 0;
}

static av_cold int utah_dec_end(AVCodecContext *avctx)
{
    UTAHDecContext *s = avctx->priv_data;
    avctx->release_buffer(avctx, &s->picture);

    return 0;
}

AVCodec ff_utah_decoder = {
    .name           = "utah",
    .type           = AVMEDIA_TYPE_VIDEO,
    .id             = AV_CODEC_ID_UTAH,
    .priv_data_size = sizeof(UTAHDecContext),
    .init           = utah_dec_init,
    .close          = utah_dec_end,
    .decode         = decode_frame,
    .capabilities   = CODEC_CAP_DR1 /*| CODEC_CAP_DRAW_HORIZ_BAND*/,
    .long_name      = NULL_IF_CONFIG_SMALL("UTAH image"),
};
