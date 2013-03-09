/*
 * PNG image format
 * Copyright (c) 2003 Fabrice Bellard
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
#include "avcodec.h"
#include "internal.h"
#include "bytestream.h"
#include "dsputil.h"


#include "libavutil/avassert.h"
  
typedef struct UTAHEncContext {
  AVFrame picture;

}UTAHEncContext;


static int encode_frame(AVCodecContext *avctx, AVPacket *pkt,
                        const AVFrame *pict, int *got_packet)
{
    UTAHEncContext *s = avctx->priv_data;
    AVFrame * const p= &s->picture;
    int ret, n_bytes;
    uint8_t *buf;

    *p = *pict;
    p->pict_type= AV_PICTURE_TYPE_I;
    p->key_frame= 1;
    n_bytes = avctx->width*avctx->height+12;

    //allcating space
    if ((ret = ff_alloc_packet2(avctx, pkt, n_bytes)) < 0)
      return ret;

    //encoding the header
    buf = pkt->data;
    bytestream_put_byte(&buf, 'U');
    bytestream_put_byte(&buf, 'T');
    bytestream_put_byte(&buf, 'A');
    bytestream_put_byte(&buf, 'H');
    bytestream_put_le32(&buf, avctx->width);
    bytestream_put_le32(&buf, avctx->height);
   
    //adding individual pixels to buffer
    for (int row = 0; row < avctx->height; row++) {
      for (int col = 0; col <  avctx->width; col++)
	{
	  uint8_t * pixel = p->data[0] + row * p->linesize[0] + col;
	  bytestream_put_byte(&buf, pixel[0]);                 
	}
    }
         
    pkt->flags |= AV_PKT_FLAG_KEY;
    *got_packet = 1;
    return 0;
}


static av_cold int utah_enc_init(AVCodecContext *avctx){

   UTAHEncContext *s = avctx->priv_data;

    avcodec_get_frame_defaults(&s->picture);
    avctx->coded_frame = &s->picture;

    return 0;
}

AVCodec ff_utah_encoder = {
    .name           = "utah",
    .type           = AVMEDIA_TYPE_VIDEO,
    .id             = AV_CODEC_ID_UTAH,
    .priv_data_size = sizeof(UTAHEncContext),
    .init           = utah_enc_init,
    .encode2        = encode_frame,
    .capabilities   = CODEC_CAP_INTRA_ONLY,
    .pix_fmts       = (const enum AVPixelFormat[]){ AV_PIX_FMT_RGB8, AV_PIX_FMT_NONE },
    .long_name      = NULL_IF_CONFIG_SMALL("UTAH image"),
};
