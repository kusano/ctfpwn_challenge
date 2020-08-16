# ubuntu:18.04
FROM ubuntu@sha256:c303f19cfe9ee92badbbbd7567bc1ca47789f79303ddcef56f77687d4744cd7a AS ubuntu18

# ubuntu:20.04
FROM ubuntu@sha256:60f560e52264ed1cb7829a0d59b1ee7740d7580e0eb293aca2d722136edb1e24

COPY --from=ubuntu18 /lib/x86_64-linux-gnu/libc-2.27.so /lib227/
COPY --from=ubuntu18 /lib/x86_64-linux-gnu/ld-2.27.so /lib227/

RUN \
  apt-get update && \
  apt-get -y install --no-install-recommends xinetd nginx openssl patchelf && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/

COPY score/ /var/www/html/
COPY files/ /var/www/html/files/
COPY c_cpp.conf /etc/nginx/conf.d/
# for Docker for Windows
RUN find /var/www/html/ -type f -print | xargs chmod 644
RUN chmod 644 /etc/nginx/conf.d/c_cpp.conf

COPY setup.sh /tmp/
RUN /bin/bash /tmp/setup.sh && \
  rm /tmp/setup.sh

CMD \
  service xinetd start; \
  service nginx start; \
  echo "open http://localhost/"; \
  tail -f /dev/null
