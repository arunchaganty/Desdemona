# Create your views here.

from django.shortcuts import render_to_response as render_to_response_
from django.template.context import Context, RequestContext
from django.http import HttpResponse, HttpResponseRedirect

from web import settings

def render_to_response(request, filename, ctx={}):
    context =  RequestContext (request,
            {'user':request.user,
            'SITE_URL':settings.SITE_URL,
            'MEDIA_URL':settings.MEDIA_URL,
            })
    return render_to_response_(filename, ctx, context)

def home(request):
    return render_to_response( request, 'home.html' )

