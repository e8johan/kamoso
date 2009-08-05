/*************************************************************************************
 *  Copyright (C) 2008 by Aleix Pol <aleixpol@gmail.com>                             *
 *  Copyright (C) 2008 by Alex Fiestas <alex@eyeos.org>                              *
 *                                                                                   *
 *  This program is free software; you can redistribute it and/or                    *
 *  modify it under the terms of the GNU General Public License                      *
 *  as published by the Free Software Foundation; either version 3                   *
 *  of the License, or (at your option) any later version.                           *
 *                                                                                   *
 *  This program is distributed in the hope that it will be useful,                  *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    *
 *  GNU General Public License for more details.                                     *
 *                                                                                   *
 *  You should have received a copy of the GNU General Public License                *
 *  along with this program; if not, write to the Free Software                      *
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA   *
 *************************************************************************************/

#include "webcamretriever.h"
#include "avdevice/videodevicepool.h"
#include <QTimer>

const int refresh=1;

WebcamRetriever::WebcamRetriever(QObject* parent, int webcamId)
	: QThread(parent), mInitialized(false), mDone(false), mImageSize(640, 480)
{
	mVideoDevicePool = Kopete::AV::VideoDevicePool::self();
	m_webcamId = webcamId;
}

void WebcamRetriever::run()
{
	mVideoDevicePool->open(m_webcamId);
	mVideoDevicePool->setSize(mImageSize.width(), mImageSize.height());
	if(!mVideoDevicePool->hasDevices()){
		return;
	}
	mVideoDevicePool->startCapturing();
	mInitialized=true;
	int returnValue;
	emit initialized();
	for(;!mDone;) {
		mLock.lockForWrite();
		if(mVideoDevicePool->checkDevice() == true){
			mVideoDevicePool->getFrame();
			mVideoDevicePool->getImage(&mImage);
			mLock.unlock();
			emit imageReady();
		}else{
			qDebug() << "Device is not ok";
			markDoneFail();
		}
		msleep(refresh);
	}
	mVideoDevicePool->close();
}

bool WebcamRetriever::isAvailable() const
{
	return mInitialized && mVideoDevicePool->hasDevices();
}
