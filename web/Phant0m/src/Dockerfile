FROM node:23.9.0-alpine

WORKDIR /app

COPY ./package.json ./

RUN npm install

COPY index.js ./

COPY docker-entrypoint.sh /docker-entrypoint.sh
# Set execute permissions for necessary scripts
RUN sed -i 's/\r$//' /docker-entrypoint.sh
RUN chmod +x /docker-entrypoint.sh


EXPOSE 1337

ENTRYPOINT ["/docker-entrypoint.sh"]