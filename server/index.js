const Koa = require('koa'),
    Router = require('koa-router');


const app = new Koa();

const router = new Router();

router.get('/', async (ctx) => {
    ctx.type = "text";
    ctx.body = "Hello, World";
});

router.get('/json', async (ctx) => {
    ctx.type = "json";
    ctx.body = {
        Hello: 'World'
    };
})

app.use(router.middleware());



app.listen(4000);
console.log('App started and listening on port:', 4000);