FROM node:current-alpine

# Create app directory
RUN mkdir -p /dock/client
WORKDIR /dock/client

# add `/app/node_modules/.bin` to $PATH
# ENV PATH /dock/client/node_modules/.bin:$PATH

# Install app dependencies
# A wildcard is used to ensure both package.json AND package-lock.json are copied
# where available (npm@5+)
COPY package.json /dock/client
COPY package-lock.json /dock/client
COPY src/generated/src /dock/client/generated/src

RUN npm install
# If you are building your code for production
# RUN npm ci --only=production

# Bundle app source
COPY . /dock/client

EXPOSE 3001

CMD ["npm", "run", "start"]
