FROM alpine:3.5

MAINTAINER Yifan Gao <docker@yfgao.com>

RUN apk add --no-cache caddy

ADD Caddyfile /

ADD . /var/www

CMD ["caddy"]
