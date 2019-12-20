//
//  Tuzzi.cpp
//  Tuzzi
//
//  Created by Lyn on 2019/5/30.
//  Copyright © 2019 Vin-Ex. All rights reserved.
//

#include "Tuzzi.h"
#include "Application.h"

NAMESPACE_TUZZI_ENGINE_BEGIN

class TuzziImpl
{
public:
    TuzziImpl()
    {
        
    }
    
    bool loadApplication(SharedPtr<Application> application)
    {
        m_application = application;
        
        if (m_application)
        {
            m_application->setSize(m_width, m_height);
        }
        
        return true;
    }
    
    bool unloadApplication()
    {
        if (m_application)
        {
            m_application->destroy();
            m_application = nullptr;
            return true;
        }
        
        return false;
    }
    
    SharedPtr<Application> currentApplication()
    {
        return m_application;
    }
    
    void init()
    {
        if (m_application)
        {
            m_application->setSize(m_width, m_height);
            m_application->init();
        }
    }
    
    void setSize(int width, int height)
    {
        m_width = width;
        m_height = height;
        if (m_application)
        {
            m_application->setSize(width, height);
        }
    }
    
    void destroy()
    {
        if (m_application)
        {
            m_application->destroy();
            m_application = nullptr;
        }
    }
    
    void update()
    {
        if (m_application)
        {
            if (!m_application->isStarted())
            {
                m_application->init();
            }
            m_application->update();
        }
    }
    
private:
    SharedPtr<Application> m_application;
    unsigned int m_width;
    unsigned int m_height;
    
};

Tuzzi *Tuzzi::instance()
{
    static Tuzzi *s_instance = nullptr;
    if (s_instance == nullptr)
    {
        s_instance = new Tuzzi();
    }
    
    return s_instance;
}

Tuzzi::Tuzzi()
{
    m_impl = new TuzziImpl();
}

Tuzzi::~Tuzzi()
{
    delete m_impl;
}

bool Tuzzi::loadApplication(SharedPtr<Application> app)
{
    return m_impl->loadApplication(app);
}

bool Tuzzi::unloadApplication()
{
    return m_impl->unloadApplication();
}

SharedPtr<Application> Tuzzi::currentApplication()
{
    return m_impl->currentApplication();
}

void Tuzzi::init()
{
    m_impl->init();
}

void Tuzzi::setSize(int width, int height)
{
    m_impl->setSize(width, height);
}

void Tuzzi::destroy()
{
    m_impl->destroy();
}

void Tuzzi::update()
{
    m_impl->update();
}

NAMESPACE_TUZZI_ENGINE_END
