FROM ubuntu@sha256:c303f19cfe9ee92badbbbd7567bc1ca47789f79303ddcef56f77687d4744cd7a

RUN \
  apt-get update && \
  apt-get -y install --no-install-recommends xinetd nginx openssl && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/

COPY score/ /var/www/html/
COPY files/ /var/www/html/files/

COPY setup.sh /tmp/
RUN /bin/bash /tmp/setup.sh

RUN \
  apt-get -y remove openssl && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/

CMD \
  service xinetd start; \
  service nginx start; \
  echo "open http://localhost/"; \
  tail -f /dev/null
